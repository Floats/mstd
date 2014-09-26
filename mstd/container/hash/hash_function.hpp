#ifndef MSTD_CONTAINER_HASH_FUNCTION_HPP_
#define MSTD_CONTAINER_HASH_FUNCTION_HPP_

#include <type_traits>
#include <mstd/detail/concept.hpp>

namespace mstd {
    template <class T>
    constexpr Require<std::is_integer<T>::value, T>
        hash(T x) noexcept
    {
        return x;
    };
}  // of namespace mstd

#endif //! MSTD_CONTAINER_HASH_FUNCTION_HPP_