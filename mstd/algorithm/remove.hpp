#ifndef MSTD_ALGORITHM_REMOVE_HPP_
#define MSTD_ALGORITHM_REMOVE_HPP_

#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/find.hpp>

namespace mstd {
    //! We should understand what remove really does. It does not indeed erase
    //! elements, what it does is that bring all elements which need preservation
    //! to front the range.
    template <class Iter, class T>
    Require<ForwardIterator<Iter>(), Iter>
        remove(Iter first, Iter last, const T& val)
    {
        //! This is simply an optimization. We do not cope with elements
        //! which do not contain a bad value.
        auto next = mstd::find(first, last, val);
        if (next == last) {
            return last;
        }
        else {
            //! As a matter of fact, we can simply delegate the whole
            //! function to mstd::remove_copy which permits overlapped
            //! ranges
            auto start = next;
            return mstd::remove_copy(++next, last, start, val);
        }
    }

    template <class Iter, class Pred>
    Require<ForwardIterator<Iter>(), Iter>
        remove_if(Iter first, Iter last, Pred pred)
    {
        //! This is simply an optimization. We do not cope with elements
        //! which do not contain a bad value.
        auto next = mstd::find_if(first, last, pred);
        if (next == last) {
            return last;
        }
        else {
            //! As a matter of fact, we can simply delegate the whole
            //! function to mstd::remove_copy which permits overlapped
            //! ranges
            auto start = next;
            return mstd::remove_copy_if(++next, last, start, pred);
        }
    }

    //! \note   [first, last) and [destination, end) may overlap
    template <class InIter, class OutIter, class T>
    Require<InputIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
        remove_copy(InIter first, InIter last,
                    OutIter destination,
                    const T& val)
    {
        for (; first != last; ++first) {
            if (*first != val) {
                *destination = *first;

                ++destination;
            }
        }

        return destination;
    }

    template <class InIter, class OutIter, class Pred>
    Require<InputIterator<InIter>() && OutputIterator<OutIter>(), OutIter>
        remove_copy_if(InIter first, InIter last,
                    OutIter destination,
                    Pred pred)
    {
        for (; first != last; ++first) {
            if (!pred(*first)) {
                *destination = *first;

                ++destination;
            }
        }

        return destination;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_REMOVE_HPP_
