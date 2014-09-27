#ifndef MSTD_UTILITY_REL_OPS_HPP_
#define MSTD_UTILITY_REL_OPS_HPP_

namespace mstd {
    namespace rel_ops {
        template <class T>
        inline bool operator!=(const T& x, const T& y)
        {
            return !(x == y);
        }

        template <class T>
        inline bool operator<=(const T& x, const T& y)
        {
            return !(y < x);
        }

        template <class T>
        inline bool operator>(const T& x, const T& y)
        {
            return !(x <= y);
        }

        template <class T>
        inline bool operator>=(const T& x, const T& y)
        {
            return !(x < y);
        }

        struct comparable {};
    }  // of namespace rel_ops

    using rel_ops::comparable;
}  // of namespace mstd

#endif //! MSTD_UTILITY_REL_OPS_HPP_
