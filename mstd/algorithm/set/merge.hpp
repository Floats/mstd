#ifndef MSTD_ALGORITHM_MERGE_HPP_
#define MSTD_ALGORITHM_MERGE_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/copy.hpp>

namespace mstd {
    template <class InIter1, class InIter2, class OutIter>
    Require<InputIterator<InIter1>() && InputIterator<InIter2>() &&
            OutputIterator<OutIter>(), OutIter>
        merge(InIter1 first1, InIter1 last1,
              InIter2 first2, InIter2 last2,
              OutIter destination)
    {
        while (first1 != last1 && first2 != last2) {
            auto&& x = *first1;
            auto&& y = *first2;
            if (x < y) {
                *destination++ = x;

                ++first1;
            }
            else if (y < x) {
                *destination++ = y;

                ++first2;
            }
            else {
                // x == y
                *destination++ = x;
                *destination++ = y;

                ++first1;
                ++first2;
            }
        }

        return mstd::copy(first1, last1, mstd::copy(first2, last2, destination));
    }

    template <class InIter1, class InIter2, class OutIter, class Comp>
    Require<InputIterator<InIter1>() && InputIterator<InIter2>() &&
            OutputIterator<OutIter>(), OutIter>
        merge(InIter1 first1, InIter1 last1,
              InIter2 first2, InIter2 last2,
              OutIter destination,
              Comp cmp)
    {
        while (first1 != last1 && first2 != last2) {
            auto&& x = *first1;
            auto&& y = *first2;
            if (cmp(x, y)) {
                *destination++ = x;

                ++first1;
            }
            else if (cmp(y, x)) {
                *destination++ = y;

                ++first2;
            }
            else {
                // x == y
                *destination++ = x;
                *destination++ = y;

                ++first1;
                ++first2;
            }
        }

        return mstd::copy(first1, last1, mstd::copy(first2, last2, destination));
    }


}  // of namespace mstd

#endif //! MSTD_ALGORITHM_MERGE_HPP_
