#ifndef MSTD_ALGORITHM_UPPER_BOUND_HPP_
#define MSTD_ALGORITHM_UPPER_BOUND_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/util.hpp>

namespace mstd {

    //! \post   for each x in [ret, last), we have val < x;
    template <class Iter, class T>
    Require<ForwardIterator<Iter>(), Iter>
        upper_bound(Iter first, Iter last, const T& val)
    {
        auto len = mstd::distance(first, last);

        while (len > 0) {
            // starts a new iteration, namely, a recursion
            // only *len* and *first* are available.
            auto half = len / 2;

            auto mid = mstd::next(first, half);

            if (val < *mid) {
                // mid is a loose upper bound for val, try to find a tight bound
                // on [first, mid)
                len = half;
            }
            else {
                // mid is a lower bound for val, run the algorithm on
                // [mid + 1, mid + len)
                first = mstd::next(mid);
                len -= (half + 1);
            }

            // prepare values for next iteration done
        }

        return first;
    }

    template <class Iter, class T, class BinPred>
    Require<ForwardIterator<Iter>(), Iter>
        upper_bound(Iter first, Iter last, const T& val, BinPred pred)
    {
        auto len = mstd::distance(first, last);

        while (len > 0) {
            // starts a new iteration, namely, a recursion
            // only *len* and *first* are available.
            auto half = len / 2;

            auto mid = first;
            mstd::advance(mid, half);

            if (pred(val, *mid)) {
                // mid is a loose upper bound for val, try to find a tight bound
                // on [first, mid)
                len = half;
            }
            else {
                // mid is a lower bound for val, run the algorithm on
                // [mid + 1, mid + len)
                first = ++mid;
                len -= (half + 1);
            }

            // prepare values for next iteration done
        }

        return first;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_UPPER_BOUND_HPP_
