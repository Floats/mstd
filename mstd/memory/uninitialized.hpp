#ifndef MSTD_MEMORY_UNINITIALIZED_ALGO_HPP_
#define MSTD_MEMORY_UNINITIALIZED_ALGO_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/memory/construct.hpp>
#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/fill.hpp>
#include <mstd/algorithm/copy.hpp>

/*!
 * \brief   Range Algorithms applied to uninitialized memory regions.
 */

namespace mstd {
    template <class OutputIter, class Size, class T>
    inline Require<OutputIterator<OutputIter>() &&
            std::has_trivial_copy_constructor<value_type_t<OutputIter>>::value,
            OutputIter>
        uninitialized_fill_n(OutputIter first, Size n, const T& val)
    {
        return mstd::fill_n(first, n, val);
    }

    template <class OutputIter, class Size, class T>
    Require<OutputIterator<OutputIter>() &&
            !std::has_trivial_copy_constructor<value_type_t<OutputIter>>::value,
            OutputIter>
        uninitialized_fill_n(OutputIter first, Size n, const T& val)
    {
        for (; n > 0; --n) {
            mstd::construct(std::addressof(*first++), val);
        }

        return first;
    }

    template <class InputIter, class OutputIter>
    inline Require<InputIterator<InputIter>() && OutputIterator<OutputIter>() &&
            std::has_trivial_copy_constructor<value_type_t<InputIter>>::value,
            OutputIter>
        uninitialized_copy(InputIter first, InputIter last, OutputIter result)
    {
        return mstd::copy(first, last, result);
    }


    template <class InputIter, class OutputIter>
    Require<InputIterator<InputIter>() && OutputIterator<OutputIter>() &&
            !std::has_trivial_copy_constructor<value_type_t<InputIter>>::value,
            OutputIter>
        uninitialized_copy(InputIter first, InputIter last, OutputIter result)
    {
        for (; first != last; ++first, ++result) {
            mstd::construct(std::addressof(*result), *first);
        }

        return result;
    }

    template <class OutputIter, class T>
    inline Require<OutputIterator<OutputIter>() &&
            std::has_trivial_copy_constructor<value_type_t<OutputIter>>::value,
            OutputIter>
        uninitialized_fill(OutputIter first, OutputIter last, const T& val)
    {
        return mstd::fill(first, last, val);
    }


    template <class OutputIter, class T>
    Require<OutputIterator<OutputIter>() &&
            !std::has_trivial_copy_constructor<value_type_t<OutputIter>>::value,
            OutputIter>
        uninitialized_fill(OutputIter first, OutputIter last, const T& val)
    {
        for (; first != last; ++first, ++result) {
            mstd::construct(std::addressof(*result), val);
        }

        return result;
    }

}  // of namespace mstd

#endif //! MSTD_MEMORY_UNINITIALIZED_ALGO_HPP_
