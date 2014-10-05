#ifndef MSTD_DETAIL_MERGE_BACKWARD_HPP_
#define MSTD_DETAIL_MERGE_BACKWARD_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/reverse_iterator.hpp>
#include <mstd/algorithm/copy.hpp>

namespace mstd {
    namespace detail {
        template <class InIter1, class InIter2, class BiIter>
        Require<BidirectionalIterator<InIter1>() &&
                BidirectionalIterator<InIter2>() &&
                BidirectionalIterator<BiIter>(), BiIter>
            merge_backward(InIter1 first1, InIter1 last1,
                  InIter2 first2, InIter2 last2,
                  BiIter destination)
        {
            auto rfirst1 = mstd::make_reverse_iterator(first1);
            auto rlast1 = mstd::make_reverse_iterator(last1);
            auto rfirst2 = mstd::make_reverse_iterator(first2);
            auto rlast2 = mstd::make_reverse_iterator(last2);
            auto result = mstd::make_reverse_iterator(destination);

            while (rfirst1 != rlast1 && rfirst2 != rlast2) {
                auto&& x = *rfirst1;
                auto&& y = *rfirst2;

                if (x < y) {
                    *result++ = y;

                    ++rfirst2;
                }
                else if (y < x) {
                    *result++ = x;

                    ++rfirst1;
                }
                else {
                    // x == y
                    *result++ = x;
                    *result++ = y;

                    ++rfirst1;
                    ++rfirst2;
                }
            }

            return mstd::copy(rfirst1, rlast1,
                              mstd::copy(rfirst2, rlast2, result)).base();
        }

    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_DETAIL_MERGE_BACKWARD_HPP_
