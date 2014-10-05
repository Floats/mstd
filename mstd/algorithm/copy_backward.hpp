#ifndef MSTD_ALGORITHM_COPY_BACKWARD_HPP_
#define MSTD_ALGORITHM_COPY_BACKWARD_HPP_

#include <cstring>
#include <mstd/iterator/concept.hpp>
#include <mstd/detail/bit_copyable.hpp>

namespace mstd {
    //! note that std::memmove behaves as if a temporary buffer is used
    template <class T1, class T2>
    Require<detail::BitCopyable<T1, T2>(), T2*>
        copy_backward(T1* first, T1* last, T2* result)
    {
        const auto n = last - first;
        std::memmove(result - n, first, n * sizeof(T1));
        return result - n;
    }

    template <class InIter, class OutIter>
    Require<RandomAccessIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
        copy_backward(InIter first, InIter last, OutIter result)
    {
        for (auto n = last - first; n > 0; --n) {
            *--result = *--last;
        }

        return result;
    }

    template <class InIter, class OutIter>
    Require<InputIterator<InIter>() && !RandomAccessIterator<InIter() &&
            OutputIterator<OutIter>(), OutIter>
        copy_backward(InIter first, InIter last, OutIter result)
    {
        for (; first != last; ) {
            *--result = *--last;
        }

        return result;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_COPY_BACKWARD_HPP_
