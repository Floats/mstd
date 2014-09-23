#include <mstd/iterator/meta.hpp>
#include <mstd/iterator/util.hpp>
#include <iostream>

static_assert(std::is_same<mstd::value_type_t<int*>, int>::value, "1");
static_assert(std::is_same<mstd::value_type_t<const int*>, const int>::value, "2");
static_assert(std::is_same<mstd::reference_type_t<int*>, int&>::value, "3");
static_assert(std::is_same<mstd::reference_type_t<const int*>, const int&>::value, "3");

int main()
{
    mstd::iterator_category_t<int*> v;
    std::cout << typeid(v).name() << std::endl;

    int x[10];

    auto a = &x[0];
    auto b = &x[10];
    std::iterator_traits<const int* const>::value_type mm;
    //mstd::value_type_t<const int* const> dd;
    std::cout << typeid(mm).name() << std::endl;
    std::cout << mstd::distance(a, b) << std::endl;
}