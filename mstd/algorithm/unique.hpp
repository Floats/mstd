#ifndef MSTD_ALGORITHM_UNIQUE_HPP_
#define MSTD_ALGORITHM_UNIQUE_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/adjacent_find.hpp>

namespace mstd {
    template <class Iter>
    Require<ForwardIter<Iter>(), Iter>
        unique(Iter first, Iter last)
    {
        auto iter = mstd::adjacent_find(first, last);
        return iter == last? last: mstd::unique_copy(iter, last, iter);
    }

    template <class InIter, class OutIter>
    Require<InputIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
        unique_copy(InIter first, InIter last, OutIter result)
    {
        if (first == last) return result;

        auto prev = *first;

        *result++ = prev;

        for (++first; first != last; ++first) {
            if (prev != *first) {
                prev = *first;
                *result++ = prev;
            }
        }

        return result;
    }

    template <class Iter, class BinPred>
    Require<ForwardIter<Iter>(), Iter>
        unique(Iter first, Iter last, BinPred pred)
    {
        auto iter = mstd::adjacent_find(first, last, pred);
        return iter == last? last: mstd::unique_copy(iter, last, iter, pred);
    }

    template <class InIter, class OutIter, class BinPred>
    Require<InputIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
        unique_copy(InIter first, InIter last, OutIter result, BinPred pred)
    {
        if (first == last) return result;

        auto prev = *first;

        *result++ = prev;

        for (++first; first != last; ++first) {
            if (pred(prev, *first)) {
                prev = *first;
                *result++ = prev;
            }
        }

        return result;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_UNIQUE_HPP_
