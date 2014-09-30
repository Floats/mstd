#ifndef MSTD_ALGORITHM_ADJACENT_FIND_HPP_
#define MSTD_ALGORITHM_ADJACENT_FIND_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class ForIter>
    Require<ForwardIterator<ForIter>(), ForIter>
        adjacent_find(ForIter first, ForIter last)
    {
        for (auto prev = first++; first != last; prev = first, ++first) {
            if (*prev == *first) return prev;
        }

        return last;
    }

    template <class ForIter, class BinPred>
    Require<ForwardIterator<ForIter>(), ForIter>
        adjacent_find(ForIter first, ForIter last, BinPred pred)
    {
        for (auto prev = first++; first != last; prev = first, ++first) {
            if (pred(*prev, *first)) return prev;
        }

        return last;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_ADJACENT_FIND_HPP_
