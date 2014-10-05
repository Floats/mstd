#ifndef MSTD_DETAIL_ROTATE_WITH_BUFFER_HPP_
#define MSTD_DETAIL_ROTATE_WITH_BUFFER_HPP_

#include <mstd/algorithm/copy.hpp>
#include <mstd/algorithm/copy_backward.hpp>
#include <mstd/algorithm/rotate.hpp>
#include <mstd/iterator/util.hpp>

namespace mstd {
    namespace detail {
        template <class Iter1, class Iter2, class Distance>
        Require<Bidirectional<Iter1>() && BidirectionalIterator<Iter2>(),
                Iter1>
            rotate_with_buffer(Iter1 first, Iter1 mid, Iter1 last,
                               Distance len1,
                               Distance len2,
                               Iter2 buffer,
                               Distance buffer_size)
        {
            if (len1 <= len2 && len1 <= buffer_size) {
                auto buffer_end = mstd::copy(first, mid, buffer);
                auto ret = mstd::copy(mid, last, first);
                mstd::copy(buffer, buffer_end, ret);

                return ret;
            }
            else if (len2 <= buffer_size) {
                auto buffer_end = mstd::copy(mid, last, buffer);
                auto ret = mstd::copy_backward(first, mid, last);
                mstd::copy(buffer, buffer_end, first);

                return ret;
            }
            else {
                mstd::rotate(first, mid, last);
                return mstd::next(first, len2);
            }
        }
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_DETAIL_ROTATE_WITH_BUFFER_HPP_
