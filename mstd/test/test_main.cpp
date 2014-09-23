#include <mstd/iterator/meta.hpp>
#include <mstd/iterator/util.hpp>
#include <mstd/algorithm/copy.hpp>
#include <algorithm>
#include <iostream>
#include <utility>
#include <string>

static_assert(std::is_same<mstd::value_type_t<int*>, int>::value, "1");
static_assert(std::is_same<mstd::value_type_t<const int*>, const int>::value, "2");
static_assert(std::is_same<mstd::reference_type_t<int*>, int&>::value, "3");
static_assert(std::is_same<mstd::reference_type_t<const int*>, const int&>::value, "3");

int main()
{
    const char x[] = "abc";
    char y[10] {};

    mstd::copy(std::begin(x), std::end(x), std::begin(y));

    std::cout << &y[0] << std::endl;
}