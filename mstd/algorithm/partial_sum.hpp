#ifndef MSTD_ALGORITHM_PARTIAL_SUM_HPP_
#define MSTD_ALGORITHM_PARTIAL_SUM_HPP_

namespace mstd {
    template <class InputIter, class OutputIter>
    inline OutputIter partial_sum(
        InputIter first, InputIter last, OutputIter result)
    {
        if (first == last) return result;

        *result = *first;

        auto acc = *first;
        for (++first, ++result; first != last; ++first, ++result) {
            acc += *first;
            *result = acc;
        }

        return result;
    }

    template <class InputIter, class OutputIter, class BinOp>
    inline OutputIter partial_sum(
        InputIter first, InputIter last, OutputIter result, BinOp op)
    {
        if (first == last) return result;

        *result = *first;

        auto acc = *first;
        for (++first, ++result; first != last; ++first, ++result) {
            acc = op(acc, *first);
            *result = acc;
        }

        return result;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_PARTIAL_SUM_HPP_
