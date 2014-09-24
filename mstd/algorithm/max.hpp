#ifndef MSTD_ALGORITHM_MAX_HPP_
#define MSTD_ALGORITHM_MAX_HPP_

/*!
*
* Note that the problem is that we use const T& and promise not to modify the input parameters. Whereas
* we can only return const T& in such cases, which may be insufficient sometimes. eg:
*   auto a = BigObj();
*   auto b = BigObj();
*   auto& c = min(a, b);
* Then we have to use c as a constant. So I eliminate all the consts.
*/

namespace mstd {
    template <class T>
    inline constexpr/*const*/ T& max(/*const*/ T& x, /*const*/ T& y)
    {
        return x < y ? y : x;
    }

    template <class T, class Cmp>
    inline constexpr/*const*/ T& max(/*const*/ T& x, /*const*/ T& y, Cmp cmp)
    {
        return cmp(x, y) ? y : x;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_MAX_HPP_
