#ifndef MSTD_ITERATOR_TAG_HPP_
#define MSTD_ITERATOR_TAG_HPP_

/*!
*
* \brief   Iterator tags
*
*/

namespace mstd {
    struct input_iterator_tag {};
    struct output_iterator_tag {};

    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}  // of namepace mstd

#endif //!MSTD_ITERATOR_TAG_HPP_