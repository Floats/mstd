#ifndef MSTD_ALGORITHM_SEARCH_HPP_
#define MSTD_ALGORITHM_SEARCH_HPP_

#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter1, class Iter2>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter1>
        search(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
    {
        for (; first1 != last1; ++first1) {
            for (auto window = first1, cursor = first2;
                 cursor != last2 && *window == *cursor;
                 ++window, ++cursor) {}

            if (cursor == last2) return first1;
        }

        return last1;
    }

    template <class Iter1, class Iter2, class BinPred>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter1>
        search(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, BinPred pred)
    {
        for (; first1 != last1; ++first1) {
            for (auto window = first1, cursor = first2;
                 cursor != last2 && pred(*window, *cursor);
                 ++window, ++cursor) {}

            if (cursor == last2) return first1;
        }

        return last1;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_SEARCH_HPP_
