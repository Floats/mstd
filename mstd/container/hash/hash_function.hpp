#ifndef MSTD_CONTAINER_HASH_FUNCTION_HPP_
#define MSTD_CONTAINER_HASH_FUNCTION_HPP_

#include <type_traits>

namespace mstd {
    using hash_code = std::size_t;

    template <class T> struct hash;

    template <>
    struct hash<int> {
        constexpr hash_code operator()(int x) const noexcept
        {
            return x;
        }
    };
}  // of namespace mstd

#endif //! MSTD_CONTAINER_HASH_FUNCTION_HPP_
