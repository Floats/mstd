#ifndef MSTD_ALGORITHM_HEAP_POP_HPP_
#define MSTD_ALGORITHM_HEAP_POP_HPP_

namespace mstd {
    template <class RandIter, class RandIter>
    inline void pop_heap(RandIter first, RandIter last);

    template <class RandIter, class RandIter, class Comp>
    inline void pop_heap(RandIter first, RandIter last, Comp comp);
} // of namespace mstd

#endif // !MSTD_ALGORITHM_HEAP_POP_HPP_
