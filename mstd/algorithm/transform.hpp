#ifndef MSTD_ALGORITHM_TRANSFORM_HPP_
#define MSTD_ALGORITHM_TRANSFORM_HPP_

#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class InIter, class OutIter, class UnaryFn>
    Require<InputIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
        transform(InIter first, InIter last, OutIter result, UnaryFn fn)
    {
        for (; first != last; ++first, ++result) {
            *result = fn(*first);
        }

        return result;
    }

    template <class InIter1, class InIter2, class OutIter, class BinaryFn>
    Require<InputIterator<InIter1>() &&
            InputIterator<InIter2>() &&
            OutputIterator<OutIter>(),
            OutIter>
        transform(InIter1 first1, InIter1 last1,
                  InIter2 first2, InIter2 last2,
                  OutIter result, BinaryFn fn)
    {
        for (; first1 != last1; ++first1, ++first2, ++result) {
            *result = fn(*first1, *first2);
        }

        return result;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_TRANSFORM_HPP_
