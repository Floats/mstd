#ifndef MSTD_ALGORITHM_PARTIAL_SORT_HPP_
#define MSTD_ALGORITHM_PARTIAL_SORT_HPP_

#include <mstd/detail/heap.hpp>
#include <mstd/algorithm/heap/make_heap.hpp>
#include <mstd/algorithm/heap/sort_heap.hpp>
#include <mstd/algorithm/swap.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter>
    Require<RandomAccessIterator<Iter>()> partial_sort(
            Iter first,
            Iter mid,
            Iter last)
    {
        if (first == mid || mid == last) return;

        mstd::make_heap(first, mid);
        mstd::detail::Heap_helper<Iter> impl{first, mid - first};

        for (auto iter = mid; iter != last; ++iter) {
            if (*iter < *first) {
                mstd::iter_swap(first, iter);
                impl.sift_down(impl.root());
            }
        }

        mstd::sort_heap(first, mid);
    }

    template <class Iter, class Comp>
    Require<RandomAccessIterator<Iter>()> partial_sort(
            Iter first,
            Iter mid,
            Iter last,
            Comp cmp)
    {
        if (first == mid || mid == last) return;

        mstd::make_heap(first, mid, cmp);
        mstd::detail::Heap_helper<Iter, Comp> impl{first, mid - first, cmp};

        for (auto iter = mid; iter != last; ++iter) {
            if (cmp(*iter, *first)) {
                mstd::iter_swap(first, iter);
                impl.sift_down(impl.root());
            }
        }

        mstd::sort_heap(first, mid, cmp);
    }

    namespace detail {
        template <class InIter, class OutIter>
        Require<InputIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
            bounded_copy(InIter& first, InIter last,
                         OutIter result_first, OutIter result_last)
        {
            while (first != last && result_first != result_last) {
                *result_first = *first;

                // update
                ++result_first;
                ++first;
            }

            return result_first;
        }
    }

    template <class InIter, class RIter>
    Require<InputIterator<InIter>() && RandomAccessIterator<RIter>(), RIter>
        partial_sort_copy(
            InIter first, InIter last,
            RIter result_first, RIter result_last)
    {
        if (first == last || result_first == result_last) return result_last;

        auto real_result_last =
                detail::bounded_copy(first, last, result_first, result_last);

        mstd::make_heap(result_first, real_result_last);
        mstd::detail::Heap_helper<Iter> impl{
            result_first,
            real_result_last - result_first
        };

        while (first != last) {
            if (*first < *result_first) {
                mstd::iter_swap(first, result_first);
                impl.sift_down(impl.root());
            }

            // update
            ++first;
        }

        mstd::sort_heap(result_first, real_result_last);

        return real_result_last;
    }

    template <class InIter, class RIter, class Comp>
    Require<InputIterator<InIter>() && RandomAccessIterator<RIter>(), RIter>
        partial_sort_copy(
            InIter first, InIter last,
            RIter result_first, RIter result_last,
            Comp cmp)
    {
        if (first == last || result_first == result_last) return result_last;

        auto real_result_last =
                detail::bounded_copy(first, last, result_first, result_last);

        mstd::make_heap(result_first, real_result_last, cmp);
        mstd::detail::Heap_helper<Iter, Comp> impl{
            result_first,
            real_result_last - result_first,
            cmp
        };

        while (first != last) {
            if (cmp(*first, *result_first)) {
                mstd::iter_swap(first, result_first);
                impl.sift_down(impl.root());
            }

            // update
            ++first;
        }

        mstd::sort_heap(result_first, real_result_last, cmp);

        return real_result_last;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_PARTIAL_SORT_HPP_
