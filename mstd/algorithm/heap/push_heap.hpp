#ifndef MSTD_ALGORITHM_HEAP_PUSH_HPP_
#define MSTD_ALGORITHM_HEAP_PUSH_HPP_

#include <mstd/detail/heap.hpp>

namespace mstd {
    template <class RandIter>
    void push_heap(RandIter first, RandIter last)
    {
        const auto n = last - first;
        if (n > 1) {
            detail::Heap_helper<RandIter> imp{first, n};

            imp.sift_up(imp.tail());
        }
    }

    template <class RandIter, class Comp>
    void push_heap(RandIter first, RandIter last, Comp cmp)
    {
        const auto n = last - first;
        if (n > 1) {
            detail::Heap_helper<RandIter, Comp> imp{first, n, cmp};

            imp.sift_up(imp.tail());
        }
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_HEAP_PUSH_HPP_
