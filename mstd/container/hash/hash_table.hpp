#ifndef MSTD_CONTAINER_HASH_TABLE_HPP_
#define MSTD_CONTAINER_HASH_TABLE_HPP_

#include <cassert>
#include <functional>
#include <vector>
#include <forward_list>
#include <initializer_list>
#include <algorithm>
#include <tuple>
#include <memory>

#include <mstd/memory/allocator.hpp>
#include <mstd/functional/identity.hpp>
#include <mstd/container/hash/hash_function.hpp>
#include <mstd/iterator/base.hpp>
#include <mstd/iterator/util.hpp>

namespace mstd {
    namespace detail {
        template <class Key, class Value,
                  class ExtractKey = identity<Value>,
                  class Hash = hash<Value>,
                  class EqualObj = std::equal_to<Value>,
                  class Allocator = allocator<Value>
                  >
        class hash_table {
        private:
            struct iterator_;
            struct const_iterator_;

        public:
            using key_type = Key;
            using value_type = Value;
            using allocator = Allocator;
            using reference = typename Allocator::reference;
            using const_reference = typename Allocator::const_reference;
            using pointer = typename Allocator::pointer;
            using const_pointer = typename Allocator::const_pointer;
            using size_type = typename Allocator::size_type;
            using difference_type = typename Allocator::difference_type;
            using iterator = iterator_;
            using const_iterator = const_iterator_;

        private:
            using node_list = std::forward_list<value_type,
                typename Allocator::template rebind<value_type>::other>;
            using bucket_vector = std::vector<node_list,
                typename Allocator::template rebind<node_list>::other>;

        private:
            friend struct iterator_;
            friend struct const_iterator_;

            struct iterator_ : public forward_iterator<value_type> {
            public:
                using self_type = iterator_;

            public:
                reference operator*()
                {
                    assert(iter_);
                    return **iter_;
                }

                pointer operator->()
                {
                    return std::addressof(this->operator*());
                }

                self_type& operator++()
                {
                    assert(iter_);

                    auto& iter = *iter_;
                    auto& obj = *iter;
                    auto& nodes = table_.get_bucket_(obj);

                    ++iter;

                    //! if the current node chain is exhausted, find the next
                    //! noexhausted chain.
                    if (iter == nodes.end()) {
                        const auto next_bnum = table_.bucket_num_(obj) + 1;

                        auto first = table_.buckets_.begin() + next_bnum;
                        auto last = table_.buckets_.end();

                        if (first < last) {
                            auto i = std::find_if(first, last, [](const node_list& v){
                                return !v.empty();
                            });

                            if (i != last) {
                                iter = (*i).begin();
                            }
                        }
                    }

                    return *this;
                }

                self_type operator++(int)
                {
                    self_type old = *this;
                    ++*this;
                    return old;
                }

                bool operator==(const self_type& other) const
                {
                    return &table_ == &other.table_ &&
                           iter_ == other.iter_;
                }

            public:
                iterator_(const self_type& other)
                    : table_(other.table_), iter_{}
                {
                    if (other.iter_) {
                        iter_.reset(new node_iterator{*other.iter_});
                    }
                }

                iterator_(self_type&&) noexcept = default;

                self_type& operator=(const self_type&) = delete;
                self_type& operator=(self_type&&) = delete;

                ~iterator_() = default;

            private:
                using node_iterator = typename node_list::iterator;

                friend class const_iterator_;
                friend class hash_table;

                iterator_(hash_table& table)
                    : table_(table)
                {
                }

                iterator_(hash_table& table, node_iterator iter)
                    : table_(table),
                      iter_{new node_iterator(iter)} // no std::make_unique now :(
                {
                }

            private:
                hash_table& table_;
                std::unique_ptr<node_iterator> iter_;
            };

            struct const_iterator_ : public forward_iterator<const value_type> {
                using self_type = const_iterator_;

                const_reference operator*() const
                {
                    assert(iter_);
                    return **iter_;
                }

                const_pointer operator->() const
                {
                    return &(this->operator*());
                }

                self_type& operator++()
                {
                    assert(iter_);

                    auto& iter = *iter_;
                    auto& obj = *iter;
                    auto& node = table_.get_bucket_(obj);

                    ++iter;

                    //! if the current node chain is exhausted, find the next
                    //! noexhausted chain.
                    if (iter == node.end()) {
                        const auto next_bnum = table_.bucket_num_(obj) + 1;

                        auto first = table_.buckets_.begin() + next_bnum;
                        auto last = table_.buckets_.end();

                        if (first < last) {
                            auto i = std::find_if(first, last, [](const node_list& v){
                                return !v.empty();
                            });

                            if (i != last) {
                                iter = (*i).begin();
                            }
                        }
                    }

                    return *this;
                }

                self_type operator++(int)
                {
                    self_type old = *this;
                    ++*this;
                    return old;
                }

                bool operator==(const self_type& other) const
                {
                    return &table_ == &other.table_ &&
                           iter_ == other.iter_;
                }

            public:
                const_iterator_(iterator_ iter)
                    : const_iterator_(iter.table_, std::move(iter.iter_))
                {}

                const_iterator_(const self_type& other)
                    : table_(other.table_), iter_{}
                {
                    if (other.iter_) {
                        iter_.reset(new node_iterator{*other.iter_});
                    }
                }

                const_iterator_(self_type&&) noexcept = default;

                self_type& operator=(const self_type&) = delete;
                self_type& operator=(self_type&&) = delete;

                ~const_iterator_() = default;

            private:
                using node_iterator = typename node_list::const_iterator;

                friend class hash_table;

                const_iterator_(hash_table& table)
                    : table_(table)
                {
                }

                const_iterator_(hash_table& table, node_iterator iter)
                    : table_(table), iter_{new node_iterator{iter}}
                {
                }

            private:
                const hash_table& table_;
                std::unique_ptr<node_iterator> iter_;
            };

        public:
            hash_table() = default;
            hash_table(ExtractKey ek, Hash hasher, EqualObj eq, Allocator alloc)
                : extract_{ek},
                  hash_{hasher},
                  equal_{eq},
                  alloc_{alloc}
            {}

            hash_table(const hash_table& other) = default;
            hash_table(hash_table&& other) = default;

            ~hash_table() = default;

        public:
            hash_table& operator=(const hash_table& other) = default;
            hash_table& operator=(hash_table&& other) = default;

        public:
            //! \name   capacity
            //! @{
            size_type size() const noexcept
            {
                return size_;
            }

            bool empty() const noexcept
            {
                return this->size() == 0;
            }

            size_type max_size() const
            {
                return alloc_.max_size();
            }
            //! @}

        public:
            //! \name iterators
            //! @{
            iterator begin()
            {
                auto iter = std::find_if(this->buckets_.begin(),
                                      this->buckets_.end(),
                                      [](const node_list& v){
                    return !v.empty();
                });

                if (iter != this->buckets_.end()) {
                    return {*this, iter->begin()};
                }
                else {
                    return this->end();
                }
            }

            const_iterator begin() const
            {
                return this->cbegin();
            }

            const_iterator cbegin() const
            {
                return {self_()->begin()};
            }

            iterator end()
            {
                return {*this};
            }

            const_iterator end() const
            {
                return this->cend();
            }

            const_iterator cend() const
            {
                return {*this};
            }
            //! @}

        public:
            //! \name   lookup
            //! @{
            size_type count(const_reference x) const
            {
                auto& nodes = get_bucket_(x);
                return std::count_if(nodes.begin(), nodes.end(),
                                     [&x, this](const_reference other){
                    return equal_(x, other);
                });
            }

            iterator find(reference obj)
            {
                auto& nodes = get_bucket_(obj);
                auto iter = std::find_if(nodes.begin(), nodes.end(),
                                      [&obj, this](const_reference other){
                    return equal_(obj, other);
                });

                if (iter != nodes.end()) {
                    return {*this, iter};
                }
                else {
                    return this->end();
                }
            }

            const_iterator find(const_reference obj) const
            {
                return {self_()->find(obj)};
            }

            std::pair<iterator, iterator> equal_range(reference obj)
            {
                auto& nodes = get_bucket_(obj);
                auto iter = std::find_if(nodes.begin(), nodes.end(),
                                       [&obj, this](const_reference other){
                     return equal_(obj, other);
                });

                if (iter != nodes.end()) {
                    auto other = iter;

                    for (; other != nodes.end() && equal_(*other, obj); ++other) {}

                    return {{*this, iter}, {*this, other}};
                }
                else {
                    return {this->end(), this->end()};
                }
            }

            std::pair<const_iterator, const_iterator>
                equal_range(reference obj) const
            {
                return {self_()->equal_range(obj)};
            }
            //! @}

        public:
            //! modifiers
            //! @{
            void clear()
            {
                buckets_.clear();
            }

            void resize(size_type num_hint)
            {
                ensure_space_(num_hint);
            }

            std::pair<iterator, bool> insert_unique(const_reference obj)
            {
                ensure_space_(this->size() + 1);
                return insert_unique_imp_(obj);
            }

            iterator insert_dup(const_reference obj)
            {
                ensure_space_(this->size() + 1);
                return insert_dup_imp_(obj);
            }

            void erase(const_reference obj)
            {
                auto& nodes = get_bucket_(obj);
                auto old = mstd::distance(nodes.begin(), nodes.end());

                nodes.remove_if([&obj, this](const_reference other){
                    return equal_(obj, other);
                });

                auto curr = mstd::distance(nodes.begin(), nodes.end());
                size_ -= (old - curr);
            }

            void erase(const_iterator iter)
            {
                this->erase(*iter);
            }

        private:
            void ensure_space_(size_type new_size)
            {
                if (new_size > this->bucket_size()) {
                    bucket_vector v(std::min(size_type(11), this->bucket_size() * 2));

                    for (auto& nodes : buckets_) {
                        for (auto& node : nodes) {
                            const auto bnum = bucket_num_(node, new_size);
                            v[bnum].push_front(std::move(node));
                        }
                    }

                    buckets_.swap(v);
                }
            }

            std::pair<iterator, bool> insert_unique_imp_(const_reference obj)
            {
                auto& nodes = get_bucket_(obj);

                // try find dups
                auto iter = std::find_if(nodes.begin(), nodes.end(),
                                      [&obj, this](const_reference other){
                    return equal_(other, obj);
                });

                if (iter != nodes.end()) {
                    return {{*this, iter}, false};
                }
                else {
                    // insert unique
                    nodes.push_front(obj);
                    ++size_;
                    return {{*this, nodes.begin()}, true};
                }
            }

            iterator insert_dup_imp_(const_reference obj)
            {
                auto& nodes = get_bucket_(obj);

                // try find dups
                auto iter = std::find_if(nodes.begin(), nodes.end(),
                                      [&obj, this](const_reference other){
                    return equal_(other, obj);
                });

                if (iter != nodes.end()) {
                    auto new_iter = nodes.insert_after(iter, obj);
                    ++size_;
                    return {*this, new_iter};
                }
                else {
                    // insert unique
                    nodes.push_front(obj);
                    ++size_;
                    return {*this, nodes.begin()};
                }
            }

            //! }

        public:
            size_type bucket_size() const
            {
                return buckets_.size();
            }

        private:
            const key_type& key_(const_reference obj) const
            {
                return extract_(obj);
            }

            size_type bucket_num_(const_reference obj, size_type n) const
            {
                return hash_(key_(obj)) % n;
            }


            size_type bucket_num_(const_reference obj) const
            {
                return bucket_num_(obj, this->size());
            }

            auto& get_bucket_(const_reference obj)
            {
                return buckets_[bucket_num_(obj)];
            }

            auto& get_bucket_(const_reference obj) const
            {
                return buckets_[bucket_num_(obj)];
            }

            hash_table& self_() const
            {
                return *const_cast<hash_table* const>(this);
            }

        private:
            bucket_vector buckets_;
            size_type size_{};
            Hash hash_{};
            ExtractKey extract_{};
            EqualObj equal_{};
            Allocator alloc_{};
        };
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_CONTAINER_HASH_TABLE_HPP_
