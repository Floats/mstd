#include <mstd/iterator/meta.hpp>
#include <mstd/iterator/util.hpp>
#include <iostream>

int main()
{
    mstd::iterator_category_t<int*> v;
    std::cout << typeid(v).name() << std::endl;

    int x[10];

    auto a = &x[0];
    auto b = &x[10];

    std::cout << mstd::distance(a, b) << std::endl;
}