#ifndef MSTD_MEMORY_ALLOCATOR_HPP_
#define MSTD_MEMORY_ALLOCATOR_HPP_

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

        template <class U>
        struct rebind {
            using other = allocator<U>;
        };

        allocator() = default;

        template <class U>
        allocator(const allocator<U>&) {}

        pointer allocate(size_type n)
        {
            return static_cast<pointer>(::operator new(n * sizeof(T)));
        }

        void deallocate(pointer buffer)
        {
            ::operator delete(buffer);
        }

        void deallocate(pointer buffer, size_type n)
        {
            while (n-- > 0) {
                this->deallocate(buffer++);
            }
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

#endif //! MSTD_MEMORY_ALLOCATOR_HPP_
