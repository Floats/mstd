#include <boost/test/unit_test.hpp>

#include <mstd/iterator/meta.hpp>
#include <mstd/iterator/concept.hpp>

BOOST_AUTO_TEST_CASE(meta)
{
    static_assert(std::is_same<mstd::value_type_t<int*>, int>::value, "1");
    static_assert(std::is_same<mstd::value_type_t<const int*>, const int>::value, "2");
    static_assert(std::is_same<mstd::reference_type_t<int*>, int&>::value, "3");
    static_assert(std::is_same<mstd::reference_type_t<const int*>, const int&>::value, "4");
}

BOOST_AUTO_TEST_CASE(concept)
{
    BOOST_REQUIRE(mstd::InputIterator<int*>());
    BOOST_REQUIRE(mstd::RandomAccessIterator<int*>());
}
