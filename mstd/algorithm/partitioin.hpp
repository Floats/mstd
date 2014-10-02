#ifndef MSTD_ALGORITHM_PARTITION_HPP_
#define MSTD_ALGORITHM_PARTITION_HPP_

#include <cassert>
#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    //! Note that this algorithm is not stable, namely, the relative order
    //! between elements are not preserved.
    //! This routine is typically used as a sub routine of quick sort.
    template <class Iter, class Pred>
    Require<BidirectionalIterator<Iter>(), Iter>
        partition(Iter first, Iter last, Pred pred)
    {
        while (first != last) {
            // Loop invariants:
            //  [beg, first) pred is true
            //  [first, last) elements not processed yet
            //  [last, end) pred is false

            // spot the first element not satisfying pred
            while (first != last && pred(*first)) ++first;
            while (first != last && !pred(*--last)) {}

            if (first != last) {
                mstd::iter_swap(first, last);

                ++first;
            }
        }

        return first;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_PARTITION_HPP_
