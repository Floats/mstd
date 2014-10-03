#ifndef MSTD_ALGORITHM_SHUFFLE_HPP_
#define MSTD_ALGORITHM_SHUFFLE_HPP_

#include <random>
#include <type_traits>
#include <mstd/iterator/concept.hpp>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    template <class Iter, class Gen>
    Require<RandomAccessIterator<Iter>()>
        shuffle(Iter first, Iter last, Gen&& gen)
    {
        using Diff_t = difference_type_t<Iter>;
        using UDiff_t = typename std::make_unsigned<Diff_t>::type;
        using Uniform_int_dist = std::uniform_int_distribution<UDiff_t>;
        using Param_t = typename Uniform_int_dist::param_type;

        Uniform_int_dist dist;

        for (auto n = last - first, i = 0; i < n; ++i) {
            //! note that i is included because the element can stay in its
            //! original place.

            //! \note   If we qualified the name, it will be bound immediately,
            //!         even if we have a better swap in mstd for an UDT.
            //!         That is to say, the overload for swap is via ADL, not
            //!         refinement for std::swap.

            //! \fixme
            //!     This is an unavoidable bug. If I don't qualify the name,
            //!     ADL will be used. For std items which have a swap by nature,
            //!     a collision with mstd::swap will occurred.
            mstd::swap(first[i], first[dist(gen, Param_t{i, n - 1})]);
        }
    }
}  // of namespace mstd

#endif //! MSTD_ALGORITHM_SHUFFLE_HPP_
