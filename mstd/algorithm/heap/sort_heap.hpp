#ifndef MSTD_ALGORITHM_HEAP_SORT_HPP_
#define MSTD_ALGORITHM_HEAP_SORT_HPP_

#include <mstd/algorithm/heap/pop_heap.hpp>

namespace mstd {
    template <class RandIter, class RandIter>
    void sort_heap(RandIter first, RandIter last)
    {
        for (; first != last; --last) {
            pop_heap(first, last);
        }
    }

    template <class RandIter, class RandIter, class Comp>
    void sort_heap(RandIter first, RandIter last, Comp cmp)
    {
        for (; first != last; --last) {
            pop_heap(first, last, cmp);
        }
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_HEAP_SORT_HPP_
