#ifndef MSTD_ITERATOR_CONCEPT_HPP_
#define MSTD_ITERATOR_CONCEPT_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/iterator/meta.hpp>
#include <mstd/iterator/tag.hpp>
#include <type_traits>

namespace mstd {
    namespace detail {
        template <class Iter, class IterTag>
        constexpr bool belong_()
        {
            using T = iterator_category_t<Iter>;
            return std::is_base_of<IterTag, T>::value;
        }
    }  // of namespace detail

    template <class Iter>
    constexpr bool InputIterator()
    {
        return detail::belong_<Iter, input_iterator_tag>();
    }

    template <class Iter>
    constexpr bool OutputIterator()
    {
        return detail::belong_<Iter, output_iterator_tag>();
    }

    template <class Iter>
    constexpr bool ForwardIterator()
    {
        return detail::belong_<Iter, forward_iterator_tag>();
    }

    template <class Iter>
    constexpr bool BidirectionalIterator()
    {
        return detail::belong_<Iter, bidirectional_iterator_tag>();
    }

    template <class Iter>
    constexpr bool RandomAccessIterator()
    {
        return detail::belong_<Iter, random_access_iterator_tag>();
    }
}  // of namespace mstd

#endif //! MSTD_ITERATOR_CONCEPT_HPP_
