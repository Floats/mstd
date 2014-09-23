#ifndef MSTD_ITERATOR_META_HPP_
#define MSTD_ITERATOR_META_HPP_

/*!
 *
 * \brief meta functions for Iterator
 *
 * Note that we only need to specialized T* and const T* for T* const are not wriable such that
 * they are both not random access iterators.
 *
 */

#include <cstddef>
#include <mstd/iterator/tag.hpp>

namespace mstd {
    //! Iterator Category
    //! @{
    template <class Iterator>
    struct iterator_category {
        using type = typename Iterator::iterator_category;
    };

    template <class T>
    struct iterator_category<T*> {
        using type = random_access_iterator_tag;
    };

    template <class Iterator>
    using iterator_category_t = typename iterator_category<Iterator>::type;
    //! @}

    //! Iterator Value Type
    //! @{
    template <class Iterator>
    struct value_type {
        using type = typename Iterator::value_type;
    };

    template <class T>
    struct value_type<T*> {
        using type = T;
    };

    template <class Iterator>
    using value_type_t = typename value_type<Iterator>::type;
    //! @}

    //! Iterator Difference Type
    //! @{
    template <class Iterator>
    struct difference_type {
        using type = typename Iterator::difference_type;
    };

    template <class T>
    struct difference_type<T*> {
        using type = std::ptrdiff_t;
    };

    template <class Iterator>
    using difference_type_t = typename difference_type<Iterator>::type;
    //! @}

    //! Iterator Pointer Type
    //! @{
    template <class Iterator>
    struct pointer_type {
        using type = typename Iterator::pointer_type;
    };

    template <class T>
    struct pointer_type<T*> {
        using type = T*;
    };

    template <class Iterator>
    using pointer_type_t = typename pointer_type<Iterator>::type;
    //! @}

    //! Iterator Reference Type
    //! @{
    template <class Iterator>
    struct reference_type {
        using type = typename Iterator::reference_type;
    };

    template <class T>
    struct reference_type<T*> {
        using type = T&;
    };

    template <class Iterator>
    using reference_type_t = typename reference_type<Iterator>::type;
    //! @}
}  // of namepace mstd

#endif //!MSTD_ITERATOR_META_HPP_