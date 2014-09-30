#ifndef MSTD_ALGORITHM_FIND_END_HPP_
#define MSTD_ALGORITHM_FIND_END_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/search.hpp>

namespace mstd {
    ////////////////////////////////////////////////////////////////////////////
    ///
    //! find_end
    //!     find the last occurrence of the second sequence in the first sequence

    //! brute force
    template <class Iter1, class Iter2>
    Require<ForwardIterator<Iter1>() && ForwardIterator<Iter2>() &&
            !BidirectionalIterator<Iter1>() && !BidirectionalIterator<Iter2>(),
            Iter1>
        find_end(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
    {
        if (first2 == last2) return last1;
        else {
            auto candidate_result = last1;

            for (; first1 != last1; ++first1) {
                first1 = mstd::search(first1, last1, first2, last2);
                if (first1 != last1) candidate_result = first1;
            }

            return candidate_result;
        }
    }

    template <class Iter1, class Iter2>
    Require<BidirectionalIterator<Iter1>() && BidirectionalIterator<Iter2>(),
            Iter1>
        find_end(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
    {
        static_assert(false, "Not implemented yet");
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_FIND_END_HPP_
