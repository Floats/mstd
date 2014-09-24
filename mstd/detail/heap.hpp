#ifndef MSTD_DETAIL_HEAP_HPP_
#define MSTD_DETAIL_HEAP_HPP_

/*!
 *
 * \brief   primatives for heap
 */

#include <cassert>
#include <functional>
#include <mstd/iterator/meta.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    namespace detail {
        /*!
         *
         * @invariant   Cmp(child, parent);
         */
        template <class RandIter,
                  class Cmp = std::less<value_type_t<RandIter>>
                  >
        struct Heap_helper {
            using Diff_type = difference_type_t<RandIter>;
            using Handle_type = difference_type_t<RandIter>;

            Heap_helper(RandIter first, Diff_type n, Cmp cmp = {})
                : elem_(first), n_(n), cmp_(cmp)
            {
            }

            Diff_type size() const
            {
                return n_;
            }

            constexpr Handle_type root() const
            {
                return 0;
            }

            constexpr Handle_type tail() const
            {
                return n_ - 1;
            }

            bool has_child(Handle_type h) const
            {
                return this->right_child(h) <= this->size();
            }

            bool has_left_child(Handle_type h) const
            {
                return this->left_child(h) < this->size();
            }

            bool has_right_child(Handle_type h) const
            {
                return this->right_child(h) < this->size();
            }

            bool has_parent(Handle_type h) const
            {
                return h != 0;
            }

            Handle_type parent(Handle_type h) const
            {
                assert(this->has_parent(h));
                return (h + 1) / 2 - 1;
            }

            Handle_type left_child(Handle_type h) const
            {
                return 2 * h + 1;
            }

            Handle_type right_child(Handle_type h) const
            {
                return 2 * h + 2;
            }

            void sift_up(Handle_type h)
            {
                assert(h != this->root());

                auto curr = h;
                while (this->has_parent(curr)) {
                    const auto par = this->parent(curr);

                    if (cmp_(elem_[curr], elem_[par])) {
                        break;
                    }
                    else {
                        mstd::swap(elem_[par], elem_[curr]);

                        // update
                        curr = par;
                    }
                }
            }

            void sift_down(Handle_type h)
            {
                auto curr = h;

                while (this->has_left_child(curr)) {
                    auto candidate = this->left_child(curr);
                    if (this->has_right_child(curr)) {
                        auto rc = this->right_child(curr);
                        candidate = cmp_(elem_[candidate], elem_[rc])?
                                        rc:
                                        candidate;
                    }

                    if (cmp_(elem_[candidate], elem_[curr])) {
                        break;
                    }
                    else {
                        // update
                        mstd::swap(elem_[curr], elem_[candidate]);
                        curr = candidate;
                    }
                }
            }

        private:
            RandIter elem_;
            Diff_type n_;
            Cmp cmp_;
        };
    } // of namespace detail
} // of namespace mstd

#endif // !MSTD_DETAIL_HEAP_HPP_
