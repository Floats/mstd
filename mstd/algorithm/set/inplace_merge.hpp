#ifndef MSTD_ALGORITHM_INPLACE_MERGE_HPP_
#define MSTD_ALGORITHM_INPLACE_MERGE_HPP_

#include <cassert>
#include <memory>
#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/util.hpp>
#include <mstd/detail/merge_with_buffer.hpp>
#include <mstd/detail/merge_without_buffer.hpp>
#include <mstd/memory/temporary_buffer.hpp>

namespace mstd {
    template <class Iter>
    Require<BidirectionalIterator<Iter>()>
        inplace_merge(Iter first, Iter mid, Iter last)
    {
        auto len1 = mstd::distance(first, mid);
        auto len2 = mstd::distance(mid, last);

        temporary_buffer buffer{len1 + len2};
        if (buffer.size() == 0) {
            detail::merge_without_buffer(first, mid, last, len1, len2);
        }
        else {
            detail::merge_with_buffer(first, mid, last,
                                      len1, len2,
                                      buffer.begin(), buffer.size());
        }
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_INPLACE_MERGE_HPP_
