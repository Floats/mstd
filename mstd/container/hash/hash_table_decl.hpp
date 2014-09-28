#ifndef MSTD_CONTAINER_HASH_TABLE_DECL_HPP_
#define MSTD_CONTAINER_HASH_TABLE_DECL_HPP_

#include <cassert>
#include <functional>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <tuple>
#include <memory>

#include <mstd/memory/allocator.hpp>
#include <mstd/functional/identity.hpp>
#include <mstd/container/hash/hash_function.hpp>
#include <mstd/iterator/base.hpp>
#include <mstd/iterator/util.hpp>
#include <mstd/utility/rel_ops.hpp>

namespace mstd {
    namespace detail {
        template <class Key, class Value,
                  class ExtractKey = identity<Value>,
                  class Hash = hash<Value>,
                  class EqualObj = std::equal_to<Value>,
                  class Allocator = allocator<Value>
                  >
        class hash_table : private comparable {
        private:
            struct iterator_;
            struct const_iterator_;

            template <class Derived, class ValueType>
            friend struct hash_iterator_mixin;

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

        public:
            hash_table()
                : hash_table({}, {}, {}, {})
            {
            }

            //! \todo   fix compiler bug: {} not usable for copy ctor
            hash_table(ExtractKey ek, Hash hasher, EqualObj eq, Allocator alloc)
                : buckets_(1),
                  hash_(hasher),
                  extract_(ek),
                  equal_(eq),
                  alloc_(alloc)
            {
            }

            //! use default five functions

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

            size_type max_size() const noexcept
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
                return {self_().begin()};
            }

            iterator end()
            {
                return iterator{*this};
            }

            const_iterator end() const
            {
                return this->cend();
            }

            const_iterator cend() const
            {
                return const_iterator{*this};
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

            iterator find(const_reference obj)
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
                return {self_().find(obj)};
            }

            std::pair<iterator, iterator> equal_range(const_reference obj)
            {
                auto& nodes = get_bucket_(obj);
                auto iter = std::find_if(nodes.begin(), nodes.end(),
                                       [&obj, this](const_reference other){
                     return equal_(obj, other);
                });

                if (iter != nodes.end()) {
                    assert(equal_(*iter, obj));

                    auto other = iter;

                    for (++other;
                         other != nodes.end() && equal_(*other, obj);
                         ++other) {
                        assert(equal_(*other, obj));
                    }

                    return {{*this, iter}, {*this, other}};
                }
                else {
                    return {this->end(), this->end()};
                }
            }

            std::pair<const_iterator, const_iterator>
                equal_range(const_reference obj) const
            {
                return {self_().equal_range(obj)};
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
                    bucket_vector v(std::min(size_type(1), this->bucket_size() * 2));

                    for (auto& nodes : buckets_) {
                        for (auto& node : nodes) {
                            const auto bnum = bucket_num_(node);
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

            size_type bucket_num_(const_reference obj) const
            {
                assert(buckets_.size());
                return hash_(key_(obj)) % buckets_.size();
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
            Hash hash_;
            ExtractKey extract_;
            EqualObj equal_;
            Allocator alloc_;
        };
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_CONTAINER_HASH_TABLE_DECL_HPP_
