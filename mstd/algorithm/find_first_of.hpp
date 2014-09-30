#ifndef MSTD_ALGORITHM_FIND_FIRST_OF_HPP_
#define MSTD_ALGORITHM_FIND_FIRST_OF_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter1, class Iter2>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter1>
        find_first_of(Iter1 corpus_first, Iter1 corpus_last,
                      Iter2 pat_first, Iter2 pat_last)
    {
        for (; corpus_first != corpus_last; ++corpus_first) {
            // for each element in corpus, check if it is occurred
            // in any of pat
            auto& elem = *corpus_first;

            for (auto cursor = pat_first; cursor != pat_last; ++cursor) {
                if (elem == *cursor) return corpus_first;
            }
        }

        return corpus_first;
    }

    template <class Iter1, class Iter2, class BinPred>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter1>
        find_first_of(Iter1 corpus_first, Iter1 corpus_last,
                      Iter2 pat_first, Iter2 pat_last,
                      BinPred pred)
    {
        for (; corpus_first != corpus_last; ++corpus_first) {
            // for each element in corpus, check if it is occurred
            // in any of pat
            auto& elem = *corpus_first;

            for (auto cursor = pat_first; cursor != pat_last; ++cursor) {
                if (pred(elem, *cursor)) return corpus_first;
            }
        }

        return corpus_first;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_FIND_FIRST_OF_HPP_
