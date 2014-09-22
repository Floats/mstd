#ifndef MSTD_ALGORITHM_ACCUMULATE_HPP_
#define MSTD_ALGORITHM_ACCUMULATE_HPP_

/*!
*
* \file     accumulate.hpp
* \author   Wu QQ AT lv.yrui@foxmail.com
* \brief    also known as reduce
* \since
*
*/


*/

namespace mstd {
    template <class InputIter, class T>
    inline T accumulate(InputIter first, InputIter last, T init)
    {
        for (; first != last; ++first) {
            init += *first;
        }

        return init;
    }

    template <class InputIter, class T, class BinOp>
    inline T accumulate(InputIter first, InputIter last, T init, BinOp op)
    {
        for (; first != last; ++first) {
            init = op(init, *first);
        }

        return init;
    }
} // of namespace mstd

#endif // !MSTD_ALGORITHM_ACCUMULATE_HPP_
