#ifndef MSTD_ALGORITHM_FOR_EACH_HPP_
#define MSTD_ALGORITHM_FOR_EACH_HPP_

#include <utility>
#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {

    /* Note that if the input range is mutable, then we can mutate its content
     * by pass reference to fn.
     * Otherwise, fn should not mutate the value in the range.
     */
    template <class Iter, class UnaryFn>
    Require<InputIterator<Iter>, UnaryFn>
        for_each(Iter first, Iter last, UnaryFn fn)
    {
        for (; first != last; ++first) {
            fn(*first);
        }

        return std::move(fn);
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_FOR_EACH_HPP_
