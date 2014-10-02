#ifndef MSTD_ALGORITHM_REVERSE_HPP_
#define MSTD_ALGORITHM_REVERSE_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    template <class Iter>
    Require<BidirectionalIterator<Iter>() && !RandomAccessIterator<Iter>()>
        reverse(Iter first, Iter last)
    {
        for (; first != last; ++first) {
            if (first != --last) {
                mstd::iter_swap(first, last);
            }
        }
    }

    template <class Iter>
    Require<RandomAccessIterator<Iter>()>
        reverse(Iter first, Iter last)
    {
        for (; first < last; ) {
            mstd::iter_swap(first++, --last);
        }
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_REVERSE_HPP_
