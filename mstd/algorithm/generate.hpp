#ifndef MSTD_ALGORITHM_GENERATE_HPP_
#define MSTD_ALGORITHM_GENERATE_HPP_

#include <mstd/detail/concept.hpp>
#include <mstd/iterator/concept.hpp>

namespace mstd {
    template <class Iter, class Generator>
    Require<OutputIterator<Iter>()>
        generate(Iter first, Iter last, Generator gen)
    {
        for (; first != last; ++first) {
            *first = gen();
        }
    }

    template <class Iter, class Size, class Generator>
    Require<OutputIterator<Iter>(), Iter>
        generate_n(Iter first, Size n, Generator gen)
    {
        for (; n > 0; ++first, --n) {
            *first = gen();
        }

        return first;
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_GENERATE_HPP_
