#ifndef MSTD_ALGORITHM_LOWER_BOUND_HPP
#define MSTD_ALGORITHM_LOWER_BOUND_HPP

#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/util.hpp>

/*!
 * Find the lower bound for a specific value in a sorted range.
 * Lower bound means:
 *      Assume ret is the returned iterator, then we have:
 *      For each value x in [first, ret) the value satisfied pred(x, val)
 *
 * Note also that we only have less operation defined on T.
 *
 * In order to produce compact code, we use iteration instead of recursion.
 *
 */

namespace mstd {
    //! I deem that there is no need to write a random access version.
    template <class Iter, class T>
    Require<ForwardIterator<Iter>(), Iter>
        lower_bound(Iter first, Iter last, const T& val)
    {
        auto len = mstd::distance(first, last);

        while (len > 0) {
            // starts a new iteration, namely, a recursion
            // only *len* and *first* are available.
            auto half = len / 2;

            auto mid = first;
            mstd::advance(mid, half);

            if (*mid < val) {
                // mid is a loose lower bound for val, try to find a tight bound
                first = ++mid;
                len -= (half + 1);
            }
            else {
                // mid is a upper bound for val, run the algorithm on [first, mid)
                len = half;
            }

            // prepare values for next iteration done
        }

        return first;
    }

    //! I deem that there is no need to write a random access version.
    template <class Iter, class T, class BinPred>
    Require<ForwardIterator<Iter>(), Iter>
        lower_bound(Iter first, Iter last, const T& val, BinPred pred)
    {
        auto len = mstd::distance(first, last);

        while (len > 0) {
            // starts a new iteration, namely, a recursion
            // only *len* and *first* are available.
            auto half = len / 2;

            auto mid = first;
            mstd::advance(mid, half);

            if (pred(*mid, val)) {
                // mid is a loose lower bound for val, try to find a tight bound
                first = ++mid;
                len -= (half + 1);
            }
            else {
                // mid is a upper bound for val, run the algorithm on [first, mid)
                len = half;
            }

            // prepare values for next iteration done
        }

        return first;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_LOWER_BOUND_HPP
