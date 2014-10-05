#ifndef MSTD_DETAIL_BIT_COPYABLE_HPP_
#define MSTD_DETAIL_BIT_COPYABLE_HPP_

#include <type_traits>

namespace mstd {
    namespace detail {
        template <class T1, class T2>
        constexpr bool BitCopyable()
        {
            using t1 = typename std::remove_const<T1>::type;
            return std::has_trivial_copy_assign<T1>::value &&
                   std::is_same<t1, T2>::value;
        }
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_DETAIL_BIT_COPYABLE_HPP_
