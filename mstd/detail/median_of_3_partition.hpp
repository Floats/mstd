#ifndef MSTD_DETAIL_MEDIAN_OF_3_PARTITION_HPP_
#define MSTD_DETAIL_MEDIAN_OF_3_PARTITION_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/meta.hpp>
#include <mstd/algorithm/partitioin.hpp>

namespace mstd {
    namespace detail {
        template <class T>
        const T& mo3(const T& a, const T& b, const T& c)
        {
            if (a < b) {
                if (b < c) {
                    return b;
                }
                else if (a < c) {
                    return c;
                }
                else {
                    return a;
                }
            }
            else {
                if (c < b) {
                    return b;
                }
                else if (c < a) {
                    return c;
                }
                else {
                    return a;
                }
            }
        }

        template <class Iter>
        Require<RandomAccessIterator<Iter>(), Iter>
            mo3_partition(Iter first, Iter last)
        {
            const auto n = last - first;

            if (n < 2) return;

            auto& pivot = mo3(*first, *(last - 1), *(first + n / 2));

            using Val_t = value_type_t<Iter>;
            return mstd::partition(first, last, [&pivot](const Val_t& val){
                return val < pivot;
            });
        }
    }  // of namespace detail
}  // of namespace mstd

#endif //! MSTD_DETAIL_MEDIAN_OF_3_PARTITION_HPP_
