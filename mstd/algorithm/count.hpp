#ifndef MSTD_ALGORITHM_COUNT_HPP_
#define MSTD_ALGORITHM_COUNT_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/meta.hpp>

namespace mstd {
    template <class InputIter, class T>
    Require<InputIterator<InputIter>(), difference_type_t<InputIter>>
        count(InputIter first, InputIter last, const T& val)
    {
        auto n = 0;

        for (; first != last; ++first) {
            if (*first == val) ++n;
        }

        return n;
    }

    template <class InputIter, class Pred>
    Require<InputIterator<InputIter>(), difference_type_t<InputIter>>
        count_if(InputIter first, InputIter last, Pred pred)
    {
        auto n = 0;

        for (; first != last; ++first) {
            if (pred(*first)) ++n;
        }

        return n;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_COUNT_HPP_
