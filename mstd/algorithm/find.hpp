#ifndef MSTD_ALGORITHM_FIND_HPP_
#define MSTD_ALGORITHM_FIND_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter, class T>
    Require<InputIterator<Iter>, Iter>
        find(Iter first, Iter last, const T& val)
    {
        for (; first != last; ++first) {
            if (*first == val) return first;
        }

        return last;
    }

    template <class Iter, class Pred>
    Require<InputIterator<Iter>, Iter>
        find_if(Iter first, Iter last, Pred pred)
    {
        for (; first != last; ++first) {
            if (pred(*first)) return first;
        }

        return last;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_FIND_HPP_
