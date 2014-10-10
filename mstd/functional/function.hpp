#ifndef MSTD_FUNCTIONAL_FUNCTION_HPP_
#define MSTD_FUNCTIONAL_FUNCTION_HPP_

#include <type_traits>
#include <utility>

/*!
 *
 *
 * Boost的实现版本是使用一个function_buffer union，用于缓存小对象。对于大对象，使用new。
 *
 * boost::function将数据与操作分开。数据存储在function_buffer中。
 * 操作封装在vtable中。由于对应不同类型的数据，我们应该有不同的操作。当function接收对象时，
 * 使用元计算选择适应的操作函数，将其存储入vtable中。
 *
 */

namespace mstd {
    namespace detail {
        template <class T>
        using remove_ref_and_cv_t =
            typename std::remove_cv<
                typename std::remove_reference<T>::type
            >::type;
    }

    template <class SigT> class function;   // not implemented

    template <class RetT, class... ArgsT>
    class function<RetT(ArgsT...)> {
    public:
        using this_type = function;
        using result_type = RetT;

    public:
        constexpr function() noexcept : m_pImpl(nullptr) {}

        //! the conversion is required!
        constexpr function(std::nullptr_t) noexcept : function() {}

        function(const this_type& that) : m_pImpl(nullptr)
        {
            if (auto imp = that.m_pImpl) {
                m_pImpl = imp.clone();
            }
        }

        function(this_type&& that) noexcept
            : m_pImpl(that.m_pImpl)
        {
            that.m_pImpl = nullptr;
        }

        //! universal reference
        template <class FunT>
        function(FunT&& fun)
            : m_pImpl(new impl<detail::remove_ref_and_cv_t<FunT>>(std::forward<FunT>(fun)))
        {
        }

        ~function()
        {
            this->clear();
        }

        this_type& operator=(const this_type& that)
        {
            function tmp(that);
            this->swap(tmp);
            return *this;
        }

        //! note that after move, the moved-from object can be in any state!
        this_type& operator=(this_type&& that) noexcept
        {
            this->swap(that);
            return *this;
        }

        this_type& operator=(std::nullptr_t)
        {
            this->clear();
            return *this;
        }

        template <class FunT>
        this_type& operator=(FunT&& fun)
        {
            function tmp(std::forward<FunT>(fun));
            this->swap(tmp);
            return *this;
        }

    public:
        //! \fixme
        //! why no ref qualified?
        result_type operator()(ArgsT... args) const
        {
            return m_pImpl->invoke(args...);
        }

        explicit operator bool() const noexcept
        {
            return !!m_pImpl;
        }

        bool operator!() const noexcept
        {
            return !!m_pImpl;
        }

        bool empty() const noexcept
        {
            return !!m_pImpl;
        }

        //! clear operation must be noexcept!
        void clear() noexcept
        {
            if (m_pImpl) {
                m_pImpl->destroy();
                m_pImpl = nullptr;
            }
        }

        void swap(this_type& that) noexcept
        {
            auto p = m_pImpl;
            m_pImpl = that.m_pImpl;
            that.m_pImpl = p;
        }

    private:
        //! 用一个通用接口封装多态的方法。function可以存储多种functor，为了这种多态，我们
        //! 需要模板。但同时，我们又需要统一存储，因此，使用一个统一的基类。
        //! 同时，为了避免虚函数的开销，我们又不能使用传统的OOP技术。事实上，此时的基类只不
        //! 过是一个代理类。通过回调来管理子对象。
        struct impl_base {
        private:
            using invoke_operator = result_type(*)(void*, ArgsT...);
            using clone_operator = impl_base*(*)(const void*);
            using destroy_operator = void(*)(void*);

            const invoke_operator invoke_;
            const clone_operator clone_;
            const destroy_operator destroy_;

        protected:
            impl_base(invoke_operator inv, clone_operator cl, destroy_operator dtr)
                : invoke_(inv), clone_(cl), destroy_(dtr)
            {}

        public:
            result_type invoke(ArgsT... args)
            {
               return invoke_(this, args...);
            }

            impl_base* clone() const
            {
                return clone_(this);
            }

            void destroy()
            {
                destroy_(this);
            }
        };

        template <class FunT> struct impl;
        template <class FunT> friend struct impl;

        template <class FunT>
        struct impl : public impl_base {
            FunT fun_;

        public:
            //! 值copy，所以使用const&
            explicit impl(const FunT& fun)
                : impl_base(&invoke_impl, &clone_impl, &destroy_impl),
                  fun_(fun)
            {}

            explicit impl(FunT&& fun)
                : impl_base(&invoke_impl, &clone_impl, &destroy_impl),
                  fun_(std::forward<FunT>(fun))
            {}

            static result_type invoke_impl(void* self, ArgsT... args)
            {
                //! \fixme
                //! why?
                return static_cast<impl*>(static_cast<impl_base*>(self))->fun_(args...);
            }

            static impl_base* clone_impl(const void* self)
            {
                return new impl(static_cast<const impl*>(
                                    static_cast<const impl_base*>(self)
                                    )->fun_);
            }

            static void destroy_impl(void* self)
            {
                delete static_cast<impl*>(static_cast<impl_base*>(self));
            }
        };
    };

    //! \note   we don't need a function<void(ArgsT...)> version!
}  // of namespace mstd

#endif //! MSTD_FUNCTIONAL_FUNCTION_HPP_
