#ifndef MSTD_ALGORITHM_HEAP_MAKE_HPP_
#define MSTD_ALGORITHM_HEAP_MAKE_HPP_

#include <mstd/detail/heap.hpp>

namespace mstd {
    template <class RandIter>
    void make_heap(RandIter first, RandIter last)
    {
        const auto n = last - first;
        if (n > 1) {
            detail::Heap_helper<RandIter> imp{first, n};

            for (auto mid = imp.size() / 2 - 1; imp.has_parent(mid); --mid) {
                imp.sift_down(mid);
            }

            imp.sift_down(imp.root());
        }
    }

    template <class RandIter, class Comp>
    void make_heap(RandIter first, RandIter last, Comp cmp)
    {
        const auto n = last - first;
        if (n > 1) {
            detail::Heap_helper<RandIter, Comp> imp{first, n, cmp};

            for (auto mid = imp.size() / 2 - 1; imp.has_parent(mid); --mid) {
                imp.sift_down(mid);
            }

            imp.sift_down(imp.root());
        }
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_HEAP_MAKE_HPP_
