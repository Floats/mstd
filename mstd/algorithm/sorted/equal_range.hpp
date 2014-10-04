#ifndef MSTD_ALGORITHM_EQUAL_RANGE_HPP_
#define MSTD_ALGORITHM_EQUAL_RANGE_HPP_

#include <utility>
#include <mstd/algorithm/sorted/lower_bound.hpp>
#include <mstd/algorithm/sorted/upper_bound.hpp>

namespace mstd {
    template <class Iter, class T>
    Require<ForwardIterator<Iter>(), std::pair<Iter, Iter>>
        equal_range(Iter first, Iter last, const T& val)
    {
        auto len = mstd::distance(first, last);

        while (len > 0) {
            auto half = len / 2;
            auto mid = mstd::next(first, half);

            if (*mid < val) {
                first = mstd::next(mid);
                len -= (half + 1);
            }
            else if (val < *mid) {
                len = half;
            }
            else {
                auto lower = mstd::lower_bound(first, mid, val);
                auto upper = mstd::lower_bound(mid + 1, mstd::next(first, len), val);
                return {lower, upper};
            }
        }

        return {first, first};
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_EQUAL_RANGE_HPP_
