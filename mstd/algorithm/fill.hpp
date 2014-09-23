#ifndef MSTD_ALGORITHM_FILL_HPP_H_
#define MSTD_ALGORITHM_FILL_HPP_H_

namespace mstd {
    template <class ForwardIter, class T>
    inline void fill(ForwardIter first, ForwardIter last, const T& val)
    {
        for (; first != last; ++first) {
            *first = val;
        }
    }

    template <class OutputIter, class Size, class T>
    inline void fill_n(OutputIter iter, Size n, const T& val)
    {
        for (; n > 0; --n, ++iter) {
            *iter = val;
        }
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_FILL_HPP_H_
