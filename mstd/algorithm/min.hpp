#ifndef MSTD_ALGORITHM_MIN_HPP_
#define MSTD_ALGORITHM_MIN_HPP_

namespace mstd {
    template <class T>
    inline /*const*/ T& min(/*const*/ T& x, /*const*/ T& y)
    {
        return x < y ? x : y;
    }

    template <class T, class Cmp>
    inline /*const*/ T& min(/*const*/ T& x, /*const*/ T& y, Cmp cmp)
    {
        return cmp(x, y) ? x : y;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_MIN_HPP_
