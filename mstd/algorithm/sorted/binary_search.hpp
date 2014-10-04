#ifndef MSTD_ALGORITHM_BINARY_SEARCH_HPP_
#define MSTD_ALGORITHM_BINARY_SEARCH_HPP_

#include <mstd/algorithm/sorted/lower_bound.hpp>

namespace mstd {
    template <class Iter, class T>
    inline Require<ForwardIterator<Iter>(), bool>
        bindary_search(Iter first, Iter last, const T& val)
    {
        auto i = mstd::lower_bound(first, last, val);
        return i != last && !(val < *i);
    }

    template <class Iter, class T, class BinPred>
    inline Require<ForwardIterator<Iter>(), bool>
        bindary_search(Iter first, Iter last, const T& val, BinPred pred)
    {
        auto i = mstd::lower_bound(first, last, val, pred);
        return i != last && !pred(val, *i);
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_BINARY_SEARCH_HPP_
