#include <boost/test/unit_test.hpp>

#include <mstd/algorithm/copy.hpp>
#include <iterator>
#include <string>

BOOST_AUTO_TEST_CASE(copy)
{
    const char t[] = "I love";
    char q[] = "I need";
    char x[10] {};

    mstd::copy(std::begin(t), std::end(t), std::begin(x));

    BOOST_CHECK_EQUAL(std::string(t), std::string(x));

    mstd::copy(std::begin(q), std::end(q), std::begin(x));
    BOOST_CHECK_EQUAL(std::string(q), std::string(x));
}
