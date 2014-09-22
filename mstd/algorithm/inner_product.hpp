#ifndef MSTD_ALGORITHM_INNER_PRODUCT_HPP
#define MSTD_ALGORITHM_INNER_PRODUCT_HPP

namespace mstd {
    template <class InputIter1, class InputIter2, class T>
    inline T inner_product(
        InputIter1 first1, InputIter1 last1, InputIter2 first2, T init)
    {
        for (; first1 != last1; ++first1, ++first2) {
            init += (*first1 * *first2);
        }

        return init;
    }

    template <class InputIter1, class InputIter2, class T, class BinOp1, class BinOp2>
    inline T inner_product(
        InputIter1 first1, InputIter1 last1, InputIter2 first2, T init, BinOp1 acc, BinOp2 iter)
    {
        for (; first1 != last1; ++first1, ++first2) {
            init = acc(init, iter(*first1, *first2));
        }

        return init;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_INNER_PRODUCT_HPP
