#ifndef MSTD_MEMORY_CONSTRUCT_HPP_
#define MSTD_MEMORY_CONSTRUCT_HPP_

#include <new>
#include <memory>
#include <mstd/detail/concept.hpp>
#include <mstd/iterator/meta.hpp>

namespace mstd {
    template <class T1, class T2>
    inline void construct(T1* p, const T2& value)
    {
        new(p) T1{value};
    }

    template <class T>
    inline void destroy(T* p) noexcept
    {
        p->~T();
    }

    template <class ForIter>
    inline Require<std::is_trivially_destructible<value_type_t<ForIter>>::value>
        destroy(ForIter, ForIter) noexcept
    {
        /* deliberately empty */
    }

    template <class ForIter>
    inline Require<!std::is_trivially_destructible<value_type_t<ForIter>>::value>
        destroy(ForIter first, ForIter last) noexcept
    {
        for (; first != last; ++first) {
            mstd::destroy(std::addressof(*first));
        }
    }
}  // of namespace mstd

#endif //! MSTD_MEMORY_CONSTRUCT_HPP_
