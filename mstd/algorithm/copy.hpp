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
            if (std::is_same<random_access_iterator_tag, iterator_category<InputIter>>::value) {
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
        inline T2* copy_aux_(T1* first, T1* last, T2* result)
        {
            using has_trivial_copy = typename std::is_trivially_copy_assignable<T2>::type;
            using is_same = typename std::is_same<std::remove_const_t<T1>, T2>::type;
            return copy_aux_(first, last, result, 
                std::conditional_t<has_trivial_copy::value && is_same::value, 
                    std::true_type, 
                    std::false_type>{}
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
