#ifndef MSTD_ITERATOR_UTIL_HPP_
#define MSTD_ITERATOR_UTIL_HPP_

#include <cassert>
#include <mstd/iterator/meta.hpp>

namespace mstd {
    namespace detail {
        template <class InputIter>
        inline difference_type_t<InputIter> 
            distance_(InputIter first, InputIter last, input_iterator_tag)
        {
            difference_type_t<InputIter> n{};
            
            while (first != last) {
                ++first;
                ++n;
            }

            return n;
        }

        template <class RandIter>
        inline difference_type_t<RandIter> 
            distance_(RandIter first, RandIter last, random_access_iterator_tag)
        {
            return last - first;
        }

        //////////////////////////////////////////////////////////////////////////////
        template <class InputIter, class Distance>
        inline void advance_(InputIter& iter, Distance n, input_iterator_tag)
        {
            assert(n >= 0);

            while (n--) {
                ++iter;
            }
        }

        template <class BiIter, class Distance>
        inline void advance_(BiIter& iter, Distance n, bidirectional_iterator_tag)
        {
            if (n >= 0) {
                while (n--) ++iter;
            }
            else {
                while (n++) --iter;
            }
        }

        template <class RandIter, class Distance>
        inline void advance_(RandIter& iter, Distance n, random_access_iterator_tag)
        {
            iter += n;
        }
    }

    template <class Iterator>
    inline difference_type_t<Iterator> distance(Iterator first, Iterator last)
    {
        return detail::distance_(first, last, iterator_category_t<Iterator>{});
    }

    template <class Iterator, class Distance>
    inline void advance(Iterator& iter, Distance n)
    {
        detail::advance_(iter, n, iterator_category_t<Iterator>{});
    }
}

#endif  //! MSTD_ITERATOR_UTIL_HPP_