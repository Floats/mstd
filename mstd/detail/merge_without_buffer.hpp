#ifndef MSTD_DETAIL_MERGE_WITHOUT_BUFFER_HPP_
#define MSTD_DETAIL_MERGE_WITHOUT_BUFFER_HPP_

#include <cassert>
#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/swap.hpp>
#include <mstd/algorithm/rotate.hpp>

namespace mstd {
    namespace detail {
        //! Note that recursion to iteration conversion only applies to
        //! induction method.
        template <class Iter, class Distance>
        Require<BidirectionalIterator<Iter>()>
            merge_without_buffer(Iter first, Iter mid, Iter last,
                                 Distance len1,
                                 Distance len2)
        {
            //! base condition
            if (len1 == 0 || len2 == 0) {
                return;
            }
            if (len1 + len2 == 2) {
                if (*mid < *first) mstd::iter_swap(first, mid);
                return;
            }

            auto first_cut = first;
            auto second_cut = mid;

            Distance len11 {};
            Distance len22 {};

            // try to cut the ranges
            if (len1 > len2) {
                len11 = len1 / 2;
                mstd::advance(first_cut, len11);

                second_cut = mstd::lower_bound(mid, last, *first_cut);

                len22 = mstd::distance(mid, second_cut);
            }
            else {
                len22 = len2 / 2;
                mstd::advance(second_cut, len22);

                first_cut = mstd::upper_bound(first, mid, *second_cut);

                len11 = mstd::distance(first, first_cut);
            }

            auto new_mid = mstd::rotate(first_cut, mid, second_cut);

            detail::merge_without_buffer(first, first_cut, new_mid,
                                         len11, len22);
            detail::merge_without_buffer(new_mid, second_cut, last,
                                         len1 - len11,
                                         len2 - len22);
        }
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_DETAIL_MERGE_WITHOUT_BUFFER_HPP_
