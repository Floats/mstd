#ifndef MSTD_ALGORITHM_SWAP_HPP_
#define MSTD_ALGORITHM_SWAP_HPP_

#include <type_traits>

namespace mstd {
    template <class T>
    inline void swap(T&& x, T&& y)
    {
        auto tmp = std::move(x);

        x = std::move(y);
        y = std::move(tmp);
    }
    
    template <class ForwardIter1, class ForwardIter2>
    inline void iter_swap(ForwardIter1 x, ForwardIter2 y)
    {
        swap(*x, *y);
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_SWAP_HPP_
