#ifndef MSTD_DETAIL_CONCEPT_HPP_
#define MSTD_DETAIL_CONCEPT_HPP_

#include <type_traits>

namespace mstd {
    template <bool T, class Ty = void>
    using Require = typename std::enable_if<T, Ty>::type;
}  // of namespace mstd


#endif //! MSTD_DETAIL_CONCEPT_HPP_
