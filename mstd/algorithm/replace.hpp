#ifndef MSTD_ALGORITHM_REPLACE_HPP_
#define MSTD_ALGORITHM_REPLACE_HPP_

#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter, class T>
    Require<ForwardIterator<Iter>()>
        replace(Iter first, Iter last, const T& old_value, const T& new_value)
    {
        for (; first != last; ++first) {
            if (*first == old_value) *first = new_value;
        }
    }

    template <class Iter, class OutIter, class T>
    Require<ForwardIterator<Iter>() && OutputIterator<OutIter>, OutIter>
        replace_copy(Iter first, Iter last,
                     OutIter destination,
                     const T& old_value, const T& new_value)
    {
        for (; first != last; ++first, ++destination) {
            *destination = *first == old_value? new_value: *first;
        }

        return destination;
    }

    template <class Iter, class Pred, class T>
    Require<ForwardIterator<Iter>()>
        replace_if(Iter first, Iter last, Pred pred, const T& new_value)
    {
        for (; first != last; ++first) {
            if (pred(*first)) *first = new_value;
        }
    }

    template <class Iter, class OutIter, class Pred, class T>
    Require<ForwardIterator<Iter>() && OutputIterator<OutIter>, OutIter>
        replace_copy_if(Iter first, Iter last,
                     OutIter destination,
                     Pred pred,
                     const T& new_value)
    {
        for (; first != last; ++first, ++destination) {
            *destination = pred(*first)? new_value: *first;
        }

        return destination;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_REPLACE_HPP_
