#ifndef MSTD_DETAIL_MERGE_WITH_BUFFER_HPP_
#define MSTD_DETAIL_MERGE_WITH_BUFFER_HPP_

#include <mstd/iterator/util.hpp>
#include <mstd/algorithm/set/merge.hpp>
#include <mstd/algorithm/copy.hpp>
#include <mstd/algorithm/sorted/lower_bound.hpp>
#include <mstd/algorithm/sorted/upper_bound.hpp>
#include <mstd/detail/merge_backward.hpp>
#include <mstd/detail/rotate_with_buffer.hpp>

namespace mstd {
    namespace detail {
        template <class Iter, class Distance, class Pointer>
        Require<BidirectionalIterator<Iter>()>
            merge_with_buffer(Iter first, Iter mid, Iter last,
                              Distance len1,
                              Distance len2,
                              Pointer buffer,
                              Distance buffer_size)
        {
            // we only need a buffer suitable for the smaller range
            if (len1 <= len2 && buffer_size >= len1) {
                auto buffer_end = mstd::copy(first, mid, buffer);
                mstd::merge(buffer, buffer_end, mid, last, first);
            }
            else if (buffer_size >= len2) {
                assert(len2 < len1);
                auto buffer_end = mstd::copy(mid, last, buffer);
                detail::merge_backward(first, mid, buffer, buffer_end, last);
            }
            else {
                assert(buffer_size < len1);
                assert(buffer_size < len2);

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

                // The two ranges are halved:
                // values in [first, first_cut), and [mid, second_cut)
                // are less than ones in [first_cut, mid) and [second_cut, last)

                auto new_mid = rotate_with_buffer(
                                   first_cut, mid, second_cut,
                                   len1 - len11,
                                   len22,
                                   buffer, buffer_size);

                // now the left half are less than the right half

                // merge the left half
                detail::merge_with_buffer(first, first_cut, new_mid,
                                          len11, len22,
                                          buffer, buffer_size);

                detail::merge_with_buffer(new_mid, second_cut, last,
                                          len1 - len11,
                                          len2 - len22,
                                          buffer, buffer_size);
            }
        }
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_DETAIL_MERGE_WITH_BUFFER_HPP_
