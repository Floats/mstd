#ifndef MSTD_ALGORITHM_HPP_
#define MSTD_ALGORITHM_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/reverse.hpp>
#include <mstd/algorithm/copy.hpp>

namespace mstd {
    template <class Iter>
    Require<ForwardIterator<Iter>() && !BidirectionalIterator<Iter>()>
        rotate(Iter first, Iter mid, Iter last)
    {

    }

    //! The implementation for bidirectional iterators is quite tricky.
    //! (AB)^T = (A^TB^T)^T
    //!     time complexity: O(2n)
    template <class Iter>
    Require<BidirectionalIterator<Iter>() && !RandomAccessIterator<Iter>()>
        rotate(Iter first, Iter mid, Iter last)
    {
        mstd::reverse(first, mid);
        mstd::reverse(mid, last);
        mstd::reverse(first, last);
    }

    template <class Iter>
    Require<RandomAccessIterator<Iter>()>
        rotate(Iter first, Iter mid, Iter last)
    {

    }

    /*! Provided a distinct target, the implementation is quite trivial */
    template <class Iter, class OutIter>
    inline Require<ForwardIterator<Iter>() && OutputIterator<OutIter>, Iter>
        rotate_copy(Iter first, Iter mid, Iter last, OutIter destination)
    {
        return mstd::copy(first, mid, mstd::copy(mid, last, destination));
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_HPP_
