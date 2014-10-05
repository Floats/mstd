#ifndef MSTD_MEMORY_TEMPORARY_BUFFER_HPP_
#define MSTD_MEMORY_TEMPORARY_BUFFER_HPP_

#include <memory>
#include <cstddef>
#include <utility>
#include <limits>
#include <mstd/algorithm/swap.hpp>

namespace mstd {
    template <class T>
    std::pair<T*, ptrdiff_t>
        get_temporary_buffer(ptrdiff_t n)
    {
        auto nlim = ptrdiff_t(std::numeric_limits<ptrdiff_t>::max() / sizeof(T));
        if (nlim < n) {
            n = nlim;
        }

        while (n > 0) {
            if (auto tmp = ::operator new(n * sizeof(T), std::nothrow)) {
                return {tmp, n};
            }

            n /= 2;
        }

        return {nullptr, 0};
    }

    template <class T>
    void return_temporary_buffer(T* buffer)
    {
        if (buffer) ::operator delete(buffer);
    }

    template <class T>
    struct temporary_buffer {
    public:
        using self_type = temporary_buffer;
        using size_type = ptrdiff_t;
        using iterator = T*;
        using const_iterator = const T*;

        explicit temporary_buffer(size_type n) noexcept
            : temporary_buffer(mstd::get_temporary_buffer<T>(n))
        {
        }

        explicit temporary_buffer(const std::pair<T*, size_type>& buffer) noexcept
            : buffer_(buffer.first), size_(buffer.second)
        {
        }

        ~temporary_buffer()
        {
            if (buffer_) {
                mstd::return_temporary_buffer(buffer_);

                buffer_ = nullptr;
                size_ = 0;
            }
        }

        temporary_buffer(const self_type&) = delete;
        self_type& operator=(const self_type&) = delete;

        temporary_buffer(self_type&& other) noexcept
            : buffer_(other.buffer_), size_(other.size_)
        {
            other.buffer_ = nullptr;
            other.size_ = 0;
        }

        self_type& operator=(self_type&& other) noexcept
        {
            mstd::swap(buffer_, other.buffer_);
            mstd::swap(size_, other.size_);
        }

    public:
        size_type size() const noexcept { return size_; }

        iterator begin() noexcept { return buffer_; }
        iterator end() noexcept { return buffer_ + size_; }

        const_iterator begin() const noexcept { return this->cbegin(); }
        const_iterator end() const noexcept { return this->cend(); }

        const_iterator cbegin() const noexcept { return buffer_; }
        const_iterator cend() const noexcept { return buffer_ + size_; }

    private:
        T* buffer_ {};
        size_type size_ {};
    };
}  // of namespace mstd

#endif //! MSTD_MEMORY_TEMPORARY_BUFFER_HPP_
