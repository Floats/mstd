#ifndef MSTD_ALLOCATOR_HPP_
#define MSTD_ALLOCATOR_HPP_

#include <cstddef>
#include <new>
#include <limits>
#include <mstd/memory/construct.hpp>

namespace mstd {
    template <class T>
    struct allocator {
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        pointer allocate(size_type n)
        {
            return ::operator new(n * sizeof(T));
        }

        pointer deallocate(pointer buffer)
        {
            ::operator delete(buffer);
        }

        void construct(pointer p, const_reference value)
        {
            mstd::construct(p, value);
        }

        template <class... Args>
        void construct(pointer p, Args&&... args)
        {
            new(p) T(std::forward<Args>(args)...);
        }

        void destroy(pointer p)
        {
            mstd::destroy(p);
        }

        pointer address(reference x) noexcept
        {
            return std::addressof(x);
        }

        const_pointer address(const_reference x) const noexcept
        {
            return std::addressof(x);
        }

        size_type max_size() const noexcept
        {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }
    };
}  // of namespace mstd

#endif //! MSTD_ALLOCATOR_HPP_
