#ifndef MSTD_ALGORITHM_HEAP_POP_HPP_
#define MSTD_ALGORITHM_HEAP_POP_HPP_

#include <mstd/detail/heap.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    template <class RandIter>
    inline void pop_heap(RandIter first, RandIter last)
    {
        const auto n = last - first;
        if (n > 1) {
            auto end = last - 1;

            mstd::iter_swap(first, end);

            detail::Heap_helper<RandIter> imp{first, n - 1};

            imp.sift_down(imp.root());
        }
    }

    template <class RandIter, class Comp>
    inline void pop_heap(RandIter first, RandIter last, Comp comp)
    {
        const auto n = last - first;
        if (n > 1) {
            auto end = last - 1;

            mstd::iter_swap(first, end);

            detail::Heap_helper<RandIter, Comp> imp{first, n - 1, comp};

            imp.sift_down(imp.root());
        }
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_HEAP_POP_HPP_
