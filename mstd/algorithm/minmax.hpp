#ifndef MSTD_ALGORITHM_MINMAX_HPP_
#define MSTD_ALGORITHM_MINMAX_HPP_

#include <mstd/iterator/concept.hpp>

namespace mstd {
    //! Forward iterator supports multipass while input iterator doesn't.
    template <class Iter>
    Require<ForwardIterator<Iter>(), Iter>
        min_element(Iter first, Iter last)
    {
        if (first == last) return last;

        auto candidate = first;

        for (++first; first != last; ++first) {
            if (*first < *candidate) {
                candidate = first;
            }
        }

        return candidate;
    }

    template <class Iter, class Comp>
    Require<ForwardIterator<Iter>(), Iter>
        min_element(Iter first, Iter last, Comp cmp)
    {
        if (first == last) return last;

        auto candidate = first;

        for (++first; first != last; ++first) {
            if (cmp(*first, *candidate)) {
                candidate = first;
            }
        }

        return candidate;
    }

    template <class Iter>
    Require<ForwardIterator<Iter>(), Iter>
        max_element(Iter first, Iter last)
    {
        if (first == last) return last;

        auto candidate = first;

        for (++first; first != last; ++first) {
            if (*candidate < *first) {
                candidate = first;
            }
        }

        return candidate;
    }

    template <class Iter, class Comp>
    Require<ForwardIterator<Iter>(), Iter>
        max_element(Iter first, Iter last, Comp cmp)
    {
        if (first == last) return last;

        auto candidate = first;

        for (++first; first != last; ++first) {
            if (cmp(*candidate, *first)) {
                candidate = first;
            }
        }

        return candidate;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_MINMAX_HPP_
