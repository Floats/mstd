#ifndef MSTD_ALGORITHM_ADJACENT_DIFFERENCE_HPP_
#define MSTD_ALGORITHM_ADJACENT_DIFFERENCE_HPP_

namespace mstd {
    template <class InputIter, class OutputIter>
    inline OutputIter adjacent_difference(
        InputIter first, InputIter last, OutputIter result)
    {
        if (first == last) return result;

        *result = *first;

        auto prev = *first;
        for (++first, ++result; first != last; ++first, ++result) {
            auto curr = *first;

            *result = curr - prev;

            prev = curr;
        }

        return result;
    }

    template <class InputIter, class OutputIter, class BinOp>
    inline OutputIter adjacent_difference(
        InputIter first, InputIter last, OutputIter result, BinOp op)
    {
        if (first == last) return result;

        *result = *first;

        auto prev = *first;
        for (++first, ++result; first != last; ++first, ++result) {
            auto curr = *first;

            *result = op(curr, prev);

            prev = curr;
        }

        return result;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_ADJACENT_DIFFERENCE_HPP_
