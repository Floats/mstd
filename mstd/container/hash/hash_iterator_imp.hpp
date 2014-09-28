#ifndef MSTD_CONTAINER_HASH_ITERATOR_IMP_HPP_
#define MSTD_CONTAINER_HASH_ITERATOR_IMP_HPP_

#include <mstd/iterator/base.hpp>
#include <mstd/container/hash/hash_table_decl.hpp>

namespace mstd {
    namespace detail {
        template <class Derived, class ValueType>
        struct hash_iterator_mixin : public forward_iterator<ValueType> {
        private:
            using child_type = Derived;

        protected:
            ~hash_iterator_mixin() = default;

        private:
            child_type& child()
            {
                return static_cast<child_type&>(*this);
            }

            const child_type& child() const
            {
                return static_cast<const child_type&>(*this);
            }

        public:  // mixins
            //! \fix find the cause of the error
            //! where the error comes from?
            //!     Because the base class is a dependent name, so unqualified
            //!     identifiers will be resolved at definition time.
            auto& operator*() const
            {
                return *child().iter_;
            }

            auto operator->() const
            {
                return std::addressof(**this);
            }

            child_type& operator++()
            {
                auto& self = this->child();
                auto& iter = self.iter_;
                auto& obj = *iter;
                auto& nodes = self.table_.get_bucket_(obj);

                ++iter;

                //! if the current node chain is exhausted, find the next
                //! non-exhausted chain.
                if (iter == nodes.end()) {
                    const auto next_bnum = self.table_.bucket_num_(obj) + 1;

                    auto first = self.table_.buckets_.begin() + next_bnum;
                    auto last = self.table_.buckets_.end();

                    if (first < last) {
                        using ref_type = decltype(nodes);

                        auto i = std::find_if(first, last, [](ref_type v){
                            return !v.empty();
                        });

                        if (i != last) {
                            iter = i->begin();
                        }
                    }
                }

                return self;
            }

            child_type operator++(int)
            {
                child_type old = child();
                ++*this;
                return old;
            }

        protected:
            bool is_equal_with(const child_type& other) const
            {
                auto& self = this->child();
                return self.iter_ == other.iter_ &&
                       std::addressof(self.table_) == std::addressof(other.table_);
            }
        };

        template <class Key, class Value,
                  class ExtractKey,
                  class Hash,
                  class EqualObj,
                  class Allocator>
        struct hash_table<
                Key, Value, ExtractKey, Hash, EqualObj, Allocator
            >::iterator_ : public hash_iterator_mixin<iterator_, Value> {
            friend struct hash_iterator_mixin<iterator_, Value>;
            friend struct hash_table::const_iterator_;
            friend class hash_table;

            using self_type = iterator_;

        public:
            friend bool operator==(const self_type& x, const self_type& y)
            {
                return x.is_equal_with(y);
            }

        private:
            using node_iterator = typename node_list::iterator;

            explicit iterator_(hash_table &table)
                : iterator_(table, {})
            {}

            iterator_(hash_table& table, node_iterator iter)
                : table_(table),
                  iter_{iter} // no std::make_unique now :(
            {
            }

        private:
            hash_table& table_;
            node_iterator iter_;
        };

        template <class Key, class Value,
                  class ExtractKey,
                  class Hash,
                  class EqualObj,
                  class Allocator>
        struct hash_table<
                Key, Value, ExtractKey, Hash, EqualObj, Allocator
            >::const_iterator_ :
                public hash_iterator_mixin<const_iterator_, const Value> {
            friend struct hash_iterator_mixin<const_iterator_, const Value>;
            friend class hash_table;

            using self_type = const_iterator_;
            using const_node_iterator = typename node_list::const_iterator;

        public:
            friend bool operator==(const self_type& x, const self_type& y)
            {
                return x.is_equal_with(y);
            }

        public:
            const_iterator_(const iterator_& iter)
                : const_iterator_{iter.table_, iter.iter_}
            {
            }

        private:
            explicit const_iterator_(const hash_table &table)
                : const_iterator_(table, {})
            {}

            const_iterator_(
                    const hash_table& table,
                    const_node_iterator iter)
                : table_(table), iter_{iter}
            {
            }

        private:
            const hash_table& table_;
            const_node_iterator iter_;
        };
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_CONTAINER_HASH_ITERATOR_IMP_HPP_
