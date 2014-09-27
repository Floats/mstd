#ifndef MSTD_ITERATOR_BASE_HPP_
#define MSTD_ITERATOR_BASE_HPP_

/*!
 *
 * \file     iterator/base.hpp
 * \author   Wu QQ AT lv.yrui@foxmail.com
 * \brief    Base classes used to facilitate the defination of new iterators.
 * \since
 *
 */

#include <cstddef>
#include <mstd/iterator/tag.hpp>
#include <mstd/utility/rel_ops.hpp>

namespace mstd {
    template <class Category, class T, 
            class Diff = std::ptrdiff_t, 
            class Pointer = T*, class Reference = T&>
    struct iterator : private rel_ops::comparable {
        using iterator_category = Category;
        using value_type = T;
        using difference_type = Diff;
        using pointer_type = Pointer;
        using reference_type = Reference;
    };

    template <class T, class Diff = std::ptrdiff_t>
    struct input_iterator : 
        public iterator<input_iterator_tag, T, Diff> {};

    template <class T, class Diff = std::ptrdiff_t>
    struct output_iterator :
        public iterator<output_iterator_tag, T, Diff> {};

    template <class T, class Diff = std::ptrdiff_t>
    struct forward_iterator :
        public iterator<forward_iterator_tag, T, Diff> {};

    template <class T, class Diff = std::ptrdiff_t>
    struct bidirectional_iterator :
        public iterator<bidirectional_iterator_tag, T, Diff> {};

    template <class T, class Diff = std::ptrdiff_t>
    struct random_access_iterator :
        public iterator<random_access_iterator_tag, T, Diff> {};
} // of namespace mstd

#endif // !MSTD_ITERATOR_BASE_HPP_
