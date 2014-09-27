#ifndef MSTD_FUNCTIONAL_IDENTITY_HPP_
#define MSTD_FUNCTIONAL_IDENTITY_HPP_

namespace mstd {
    template <class T>
    struct identity {
        constexpr T& operator()(T& t) const noexcept
        {
            return t;
        }

        constexpr const T& operator()(const T& t) const noexcept
        {
            return t;
        }
    };
}  // of namespace mstd

#endif //! MSTD_FUNCTIONAL_IDENTITY_HPP_
