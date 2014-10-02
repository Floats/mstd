#ifndef MSTD_ALGORITHM_INCLUES_HPP_
#define MSTD_ALGORITHM_INCLUES_HPP_

#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter1, class Iter2>
    Require<InputIterator<Iter1>() && InputIterator<Iter2>(), bool>
        includes(Iter1 corpus_first, Iter1 corpus_last,
                 Iter2 pat_first, Iter2 pat_last)
    {
        while (corpus_first != corpus_last && pat_first != pat_last) {
            //! the input range may be either mutable or immutable,
            //! such that I use an universal reference which works for both
            //! rvalue or lvalue.
            auto&& corpus = *corpus_first;
            auto&& pat = *pat_first;

            if (corpus < pat) {
                ++corpus_first;
            }
            else if (pat < corpus) {
                return false;
            }
            else {
                ++corpus_first;
                ++pat_first;
            }
        }

        return pat_first == pat_last;
    }

    template <class Iter1, class Iter2, class Comp>
    Require<InputIterator<Iter1>() && InputIterator<Iter2>(), bool>
        includes(Iter1 corpus_first, Iter1 corpus_last,
                 Iter2 pat_first, Iter2 pat_last
                 Comp cmp)
    {
        while (corpus_first != corpus_last && pat_first != pat_last) {
            //! the input range may be either mutable or immutable,
            //! such that I use an universal reference which works for both
            //! rvalue or lvalue.
            auto&& corpus = *corpus_first;
            auto&& pat = *pat_first;

            if (cmp(corpus, pat)) {
                ++corpus_first;
            }
            else if (cmp(pat, corpus)) {
                return false;
            }
            else {
                // pat == corpus
                ++corpus_first;
                ++pat_first;
            }
        }

        return pat_first == pat_last;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_INCLUES_HPP_
