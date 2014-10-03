#ifndef MSTD_ALGORITHM_INPLACE_MERGE_HPP_
#define MSTD_ALGORITHM_INPLACE_MERGE_HPP_

#include <cassert>
#include <memory>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    namespace detail {
        template <class Iter, class Distance>
        Require<BidirectionalIterator<Iter>()>
            merge_without_buffer(Iter first, Iter mid, Iter last,
                                 Distance len1,
                                 Distance len2)
        {
            assert(len1 != 0 && len2 != 0);

            //! \todo
        }
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_INPLACE_MERGE_HPP_
