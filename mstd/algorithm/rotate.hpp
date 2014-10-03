#ifndef MSTD_ALGORITHM_HPP_
#define MSTD_ALGORITHM_HPP_

#include <cassert>
#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/reverse.hpp>
#include <mstd/algorithm/copy.hpp>

namespace mstd {
    /*!
     *
     * This implementation is quite obscure.
     * We can view it as a recursive solution. We first swap the common subsequence
     * with the same length of [first, mid) and [mid, last), and reduce the problem
     * to another similiar problem. Though the algorithm is a recursive algorithm,
     * we simply turn it to an iteration version for more compact code.
     *
     */
    template <class Iter>
    Require<ForwardIterator<Iter>() && !BidirectionalIterator<Iter>()>
        rotate(Iter first, Iter mid, Iter last)
    {
        for (auto first2 = mid; ;) {
            for (; first != mid && first2 != last; ++first, ++first2) {
                mstd::iter_swap(first, first2);
            }

            if (first == mid) {
                if (first2 == last) return;

                mid = first2;    // furthur swap [first, first2) and [first2, last)
            }
            else {
                assert(first2 == last);
                // furthur swap [first, mid) and [mid, last)
                first2 = mid;
            }
        }
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

    namespace detail {
        template <class T>
        T gdc(T m, T n)
        {
            while (n != 0) {
                auto modulus = m % n;

                // update
                m = n;
                n = modulus;
            }

            return m;
        }


    }  // of namespace detail

    template <class Iter>
    Require<RandomAccessIterator<Iter>()>
        rotate(Iter first, Iter mid, Iter last)
    {
        const auto total_n = last - first;
        const auto n1 = mid - first;
        auto n = detail::gdc(total_n, n1);

        //! \todo   implement this!
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
