#ifndef MSTD_ALGORITHM_NTH_ELEMENT_HPP_
#define MSTD_ALGORITHM_NTH_ELEMENT_HPP_

#include <mstd/detail/median_of_3_partition.hpp>
#include <mstd/detail/insertion_sort.hpp>

namespace mstd {
    template <class Iter>
    Require<RandomAccessIterator<Iter>()>
        nth_element(Iter first, Iter nth, Iter last)
    {
        if (first == nth || nth == last) return;

        while (last - first < detail::insertion_threshold) {
            // [first, cut) < pivot and [cut, last) >= pivot
            //! \todo   use unguarded_partition as an optimazation
            auto cut = detail::mo3_partition(first, last);
            if (cut < nth) {
                first = cut;
            }
            else {
                last = cut;
            }
        }

        detail::insertion_sort(first, last);
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_NTH_ELEMENT_HPP_
