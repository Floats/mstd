#ifndef MSTD_ALGORITHM_COPY_HPP_
#define MSTD_ALGORITHM_COPY_HPP_

#include <cstring>
#include <type_traits>
#include <mstd/iterator/meta.hpp>
#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    namespace detail {
        template <class InputIter, class OutputIter>
        require<InputIterator<InputIter>() && !RandomAccessIterator<InputIter>(), OutputIter>
            copy_imp_(InputIter first, InputIter last, OutputIter result)
        {
            static_assert(InputIterator<InputIter>() && !RandomAccessIterator<InputIter>(),
                          "bad dispatching");

            for (; first != last; ++first, ++result) {
                *result = *first;
            }

            return result;
        }

        template <class RandIter, class OutputIter>
        require<RandomAccessIterator<RandIter>(), OutputIter>
            copy_imp_(RandIter first, RandIter last, OutputIter result)
        {
            static_assert(RandomAccessIterator<RandIter>(),
                          "bad dispatching");

            auto n = last - first;
            
            for (; n > 0; --n, ++first, ++result) {
                *result = *first;
            }

            return result;
        }

        template <class InputIter, class OutputIter>
        inline OutputIter copy_aux_(InputIter first, InputIter last, OutputIter result)
        {
            return copy_imp_(first, last, result);
        }

        template <class T1, class T2>
        constexpr bool BitCopyable()
        {
            using t1 = typename std::remove_const<T1>::type;
            return std::has_trivial_copy_assign<T1>::value &&
                   std::is_same<t1, T2>::value;
        }

        template <class T1, class T2>
        inline require<BitCopyable<T1, T2>(),T2*>
            copy_aux_(T1* first, T1* last, T2* result)
        {
            const auto n = last - first;

            std::memmove(result, first, sizeof(T2) * n);

            return result + n;
        }

        template <class T1, class T2>
        inline require<!BitCopyable<T1, T2>(), T2*>
            copy_aux_(T1* first, T1* last, T2* result)
        {
            return copy_imp_(first, last, result);
        }
    } // of namespace detail

    template <class InputIter, class OutputIter>
    inline OutputIter copy(InputIter first, InputIter last, OutputIter result)
    {
        return detail::copy_aux_(first, last, result);
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_COPY_HPP_
