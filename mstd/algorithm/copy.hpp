#ifndef MSTD_ALGORITHM_COPY_HPP_
#define MSTD_ALGORITHM_COPY_HPP_

#include <cstring>
#include <type_traits>
#include <mstd/iterator/meta.hpp>

namespace mstd {
    namespace detail {
        template <class InputIter, class OutputIter>
        OutputIter copy_imp_(InputIter first, InputIter last, OutputIter result)
        {
            for (; first != last; ++first, ++result) {
                *result = *first;
            }

            return result;
        }

        template <class InputIter, class OutputIter>
        OutputIter copy_n_(InputIter first, OutputIter result, decltype(first - first) n)
        {
            for (; n > 0; --n, ++first, ++result) {
                *result = *first;
            }

            return result;
        }

        template <class InputIter, class OutputIter>
        OutputIter copy_aux_(InputIter first, InputIter last, OutputIter result)
        {
            //! Actuall I deem that this selection will be optimized out via DEAD CODE ILIMINATION
            if (std::is_same<random_access_iterator_tag, iterator_category_t<InputIter>>::value) {
                return copy_n_(first, result, last - first);
            }
            else {
                return copy_imp_(first, last, result);
            }
        }

        template <class T1, class T2>
        T2* copy_aux_(T1* first, T1* last, T2* result, std::true_type has_trivial_copy)
        {
            const auto n = last - first;

            std::memmove(result, first, sizeof(T2) * n);

            return result + n;
        }

        template <class T1, class T2>
        inline T2* copy_aux_(T1* first, T1* last, T2* result, std::false_type dont_has_trivial_copy)
        {
            return copy_n_(first, result, last - first);
        }

        template <class T1, class T2>
        struct can_accelerate_ {
            using t1 = typename std::remove_const<T1>::type;
            static constexpr bool value =
                    std::has_trivial_copy_assign<T1>::value &&
                    std::is_same<t1, T2>::value;
        };

        template <class T1, class T2>
        inline T2* copy_aux_(T1* first, T1* last, T2* result)
        {
            return copy_aux_(first, last, result, 
                typename std::conditional<
                    can_accelerate_<T1, T2>::value,
                    std::true_type, 
                    std::false_type>::type{}
            );
        }
    } // of namespace detail

    template <class InputIter, class OutputIter>
    inline OutputIter copy(InputIter first, InputIter last, OutputIter result)
    {
        return detail::copy_aux_(first, last, result);
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_COPY_HPP_
