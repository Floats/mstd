#ifndef MSTD_ALGORITHM_REVERSE_HPP_
#define MSTD_ALGORITHM_REVERSE_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    template <class Iter>
    Require<BidirectionalIterator<Iter>() && !RandomAccessIterator<Iter>()>
        reverse(Iter first, Iter last)
    {
        while (first != last) {
            if (first != --last) {
                mstd::iter_swap(first, last);

                ++first;
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

    template <class BiIter, class OutIter>
    Require<BidirectionalIterator<BiIter>() && OutputIterator<OutIter>(), OutIter>
        reverse_copy(BiIter first, BiIter last, OutIter destination)
    {
        while (first != last) {
            --last;

            *destination++ = *last;
        }

        return destination;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_REVERSE_HPP_
