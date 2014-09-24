#ifndef MSTD_ALGORITHM_MISMATCH_HPP_
#define MSTD_ALGORITHM_MISMATCH_HPP_

#include <tuple>

namespace mstd {
    template <class InputIter1, class InputIter2>
    std::pair<InputIter1, InputIter2> mismatch(
        InputIter1 first1, InputIter1 last1, InputIter2 first2)
    {
        for (; first1 != last1 && *first1 == *first2; ++first1, ++first2) {}
        
        return std::make_pair(first1, first2);
    }

    template <class InputIter1, class InputIter2, class BinPred>
    std::pair<InputIter1, InputIter2> mismatch(
        InputIter1 first1, InputIter1 last1, InputIter2 first2, BinPred pred)
    {
        for (; first1 != last1 && pred(first1, first2); ++first1, ++first2) {}

        return std::make_pair(first1, first2);
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_MISMATCH_HPP_
