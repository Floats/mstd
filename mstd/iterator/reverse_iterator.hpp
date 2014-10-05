#ifndef MSTD_ITERATOR_REVERSE_ITERATOR_HPP_
#define MSTD_ITERATOR_REVERSE_ITERATOR_HPP_

#include <memory>
#include <mstd/iterator/concept.hpp>
#include <mstd/iterator/meta.hpp>

namespace mstd {
    template <class Iterator>
    struct reverse_iterator {
        static_assert(BidirectionalIterator<Iterator>(),
                      "Bidirectional iterator required");

    public:
        using iterator_category = iterator_category_t<Iterator>;
        using value_type = value_type_t<Iterator>;
        using difference_type = difference_type_t<Iterator>;
        using pointer_type = pointer_type_t<Iterator>;
        using reference_type = reference_type_t<Iterator>;

        using iterator_type = Iterator;
        using self_type = reverse_iterator;

    public:
        explicit reverse_iterator(Iterator base) : underly_(base) {}

        reverse_iterator(const self_type& other) : underly_(other.base()) {}

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter>& other)
            : underly_(other.base())
        {}

    public:
        iterator_type base() const { return underly_; }

    public:
        reference_type operator*() const
        {
            auto tmp = underly_;
            return *--tmp;
        }

        pointer_type operator->() const
        {
            return std::addressof(**this);
        }

        self_type& operator++()
        {
            --underly_;
            return *this;
        }

        self_type operator++(int)
        {
            auto old = *this;
            --*this;
            return old;
        }

        self_type& operator--()
        {
            ++underly_;
            return *this;
        }

        self_type operator--(int)
        {
            auto old = *this;
            --*this;
            return old;
        }

        Require<RandomAccessIterator<iterator_type>(), self_type>
            operator+(difference_type_t n) const
        {
            auto dup = *this;
            dup += n;
            return dup;
        }

        Require<RandomAccessIterator<iterator_type>(), self_type&>
            operator+=(difference_type_t n) const
        {
            underly_ -= n;
            return *this;
        }

        Require<RandomAccessIterator<iterator_type>(), self_type>
            operator-(difference_type_t n) const
        {
          auto dup = *this;
          dup -= n;
          return dup;
        }

        Require<RandomAccessIterator<iterator_type>(), self_type&>
            operator-=(difference_type_t n) const
        {
          underly_ += n;
          return *this;
        }

        Require<RandomAccessIterator<iterator_type>(), reference_type>
            operator[](difference_type n) const
        {
            return *(*this + n);
        }

    private:
        Iterator underly_;
    };

    template <class Iter>
    inline Require<BidirectionalIterator<Iter>(), reverse_iterator<Iter>>
        make_reverse_iterator(Iter iter)
    {
        return reverse_iterator<Iter>(iter);
    }

    template <class Iterator>
    inline bool operator==(const reverse_iterator<Iterator>& x,
                 const reverse_iterator<Iterator>& y)
    {
        return x.base() == y.base();
    }

    template <class Iterator>
    inline Require<RandomAccessIterator<iterator_type>(), bool>
        operator<(const reverse_iterator<Iterator>& x,
                 const reverse_iterator<_Iterator>& y)
    {
        return y.base() < x.base();
    }
}  // of namespace mstd

#endif //! MSTD_ITERATOR_REVERSE_ITERATOR_HPP_
