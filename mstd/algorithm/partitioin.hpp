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
        //! \todo   I am just dazzled.
        while (first != last) {
            // spot the first element not satisfying pred
            while (first != last && pred(*first)) ++first;

            while (first != last && !pred(*last)) --last;

            // now first points to an element not satisfying pred
            // last points to an element satisfying pred
            // and first <= last
            if (first != last) {
                mstd::iter_swap(first, last);
            }
        }

        return first;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_PARTITION_HPP_
