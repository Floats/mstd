#ifndef MSTD_ALGORITHM_IOTA_HPP_
#define MSTD_ALGORITHM_IOTA_HPP_

namespace mstd {
    template <class ForwardIter, class T>
    inline void iota(ForwardIter first, ForwardIter last, T init)
    {
        for (; first != last; ++first, ++init) {
            *first = init;
        }
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_IOTA_HPP_
