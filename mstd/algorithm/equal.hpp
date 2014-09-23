#ifndef MSTD_ALGORITHM_EQUAL_HPP_
#define MSTD_ALGORITHM_EQUAL_HPP_

namespace mstd {
    template <class InputIter1, class InputIter2>
    inline bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) return false;
        }

        return true;
    }

    template <class InputIter1, class InputIter2, class BinPred>
    inline bool equal(
        InputIter1 first1, InputIter1 last1, 
        InputIter2 first2, 
        BinPred pred)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!pred(*first1, *first2)) return false;
        }

        return true;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_EQUAL_HPP_
