#ifndef MSTD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_
#define MSTD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_

#include <cstring>
#include <mstd/algorithm/min.hpp>

namespace mstd {
    /*
    // This implemenation is deficient for we can only use < operation on the element type
    template <class InputIter1, class InputIter2>
    bool lexicographical_compare(
        InputIter1 first1, InputIter1 last1, 
        InputIter2 first2, InputIter2 last2)
    {
        for (; 
            first1 != last1 && first2 != last2 && *first1 == *first2;
            ++first1, ++first2) {
        }

        if (first1 == last1) {
            return first2 != last2;
        }
        else if (first2 == last2) {
            return false;
        }
        else {
            return *first1 < *first2;
        }
    }
    */
    template <class InputIter1, class InputIter2>
    bool lexicographical_compare(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2)
    {
        for (; first1 != last1 && first2 != last2;
            ++first1, ++first2) {
            auto& x = *first1;
            auto& y = *first2;
            if (x < y) return true;
            if (y < x) return false;
        }

        return first1 == last1 && first2 != last2;
    }

    template <class InputIter1, class InputIter2, class Cmp>
    bool lexicographical_compare(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        Cmp cmp)
    {
        for (; first1 != last1 && first2 != last2;
            ++first1, ++first2) {
            auto& x = *first1;
            auto& y = *first2;
            if (cmp(x < y)) return true;
            if (cmp(y < x)) return false;
        }

        return first1 == last1 && first2 != last2;
    }

    //! specialized version
    bool lexicographical_compare(
        const unsigned char* first1, const unsigned char* last1,
        const unsigned char* first2, const unsigned char* last2)
    {
        const auto len1 = last1 - first1;
        const auto len2 = last2 - first2;

        auto ret = std::memcmp(first1, first2, min(len1, len2));

        return ret == 0 ? len1 < len2 : ret < 0;
    }

    bool lexicographical_compare(
        const char* first1, const char* last1,
        const char* first2, const char* last2)
    {
        const auto len1 = last1 - first1;
        const auto len2 = last2 - first2;

        auto ret = std::memcmp(first1, first2, min(len1, len2));

        return ret == 0 ? len1 < len2 : ret < 0;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_
