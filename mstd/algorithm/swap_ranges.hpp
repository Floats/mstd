#ifndef MSTD_ALGORITHM_SWAP_RANGES_HPP_
#define MSTD_ALGORITHM_SWAP_RANGES_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    template <class Iter1, class Iter2>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter2>
        swap_ranges(Iter1 first1, Iter1 last1, Iter2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) {
            mstd::iter_swap(first1, first2);
        }

        return first2;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_SWAP_RANGES_HPP_
