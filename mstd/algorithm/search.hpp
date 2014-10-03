#ifndef MSTD_ALGORITHM_SEARCH_HPP_
#define MSTD_ALGORITHM_SEARCH_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/util.hpp>
#include <mstd/algorithm/find.hpp>

namespace mstd {
    template <class Iter1, class Iter2>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter1>
        search(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
    {
        const auto len1 = mstd::distance(first1, last1);
        const auto len2 = mstd::distance(first2, last2);

        if (len1 >= len2) {
            for (int n = len1 - len2; n >= 0; ++first1, --n) {
                for (auto window = first1, cursor = first2;
                     cursor != last2 && *window == *cursor;
                     ++window, ++cursor) {}

                if (cursor == last2) return first1;
            }
        }

        return last1;
    }

    template <class Iter1, class Iter2, class BinPred>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>(), Iter1>
        search(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, BinPred pred)
    {
        const auto len1 = mstd::distance(first1, last1);
        const auto len2 = mstd::distance(first2, last2);

        if (len1 >= len2) {
            for (int n = len1 - len2; n >= 0; ++first1, --n) {
                for (auto window = first1, cursor = first2;
                     cursor != last2 && pred(*window, *cursor);
                     ++window, ++cursor) {}

                if (cursor == last2) return first1;
            }
        }

        return last1;
    }

    template <class Iter, class Size, class T>
    Require<ForwardIterator<Iter>(), Iter>
        search_n(Iter first, Iter last, Size n, const T& val)
    {
        if (n > 0) {
            for (auto cursor = mstd::find(first, last, val);
                 cursor != last;
                 cursor = mstd::find(first, last, val)) {
                ++cursor;

                auto require = n - 1;

                while (require > 0 && cursor != last && *cursor == val) {
                    ++cursor;
                    --require;
                }

                if (require != 0) {
                    return first;
                }
            }
        }

        return last;
    }

    //! Note that I deliberately modified the interface for the reason
    //! that I think they are equivalent provided lambdas and this version
    //! is terser.
    template <class Iter, class Size, class Pred>
    Require<ForwardIterator<Iter>(), Iter>
        search_n(Iter first, Iter last, Size n, Pred pred)
    {
        if (n > 0) {
            for (auto cursor = mstd::find_if(first, last, pred);
                 cursor != last;
                 cursor = mstd::find_if(first, last, pred)) {
                ++cursor;

                auto require = n - 1;

                while (require > 0 && cursor != last && pred(*cursor, val)) {
                    ++cursor;
                    --require;
                }

                if (require != 0) {
                    return first;
                }
            }
        }

        return last;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_SEARCH_HPP_
