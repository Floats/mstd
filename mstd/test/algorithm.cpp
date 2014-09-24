#include <boost/test/unit_test.hpp>

#include <mstd/algorithm/copy.hpp>
#include <mstd/algorithm/heap/make_heap.hpp>
#include <mstd/algorithm/heap/pop_heap.hpp>
#include <mstd/algorithm/heap/push_heap.hpp>
#include <mstd/algorithm/heap/sort_heap.hpp>
#include <iterator>
#include <string>
#include <algorithm>

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

BOOST_AUTO_TEST_CASE(push_heap)
{
    std::vector<int> v;

    v.push_back(0);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 0);

    v.push_back(3);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 3);

    v.push_back(8);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 8);

    v.push_back(2);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 8);

    v.push_back(8);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 8);

    v.push_back(2);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 8);

    v.push_back(8);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 8);

    v.push_back(12);
    mstd::push_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v[0], 12);
}

BOOST_AUTO_TEST_CASE(pop_heap)
{
    std::vector<int> v{2, 1};

    mstd::pop_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v.front(), 1);

    v = { 8, 1, 2};
    mstd::pop_heap(v.begin(), v.end());
    BOOST_CHECK_EQUAL(v.front(), 2);
    BOOST_CHECK_EQUAL(v.back(), 8);

    v = {2,3,1,3,45,3,4};
    std::make_heap(v.begin(), v.end());

    auto cv = v;

    while (!v.empty()) {
        mstd::pop_heap(v.begin(), v.end());
        std::pop_heap(cv.begin(), cv.end());

        BOOST_CHECK_EQUAL(v.front(), cv.front());
        BOOST_CHECK_EQUAL(v.back(), cv.back());

        v.pop_back();
        cv.pop_back();
    }

    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::make_heap(v.begin(), v.end());
    cv = v;

    while (!v.empty()) {
        mstd::pop_heap(v.begin(), v.end());
        std::pop_heap(cv.begin(), cv.end());

        BOOST_CHECK_EQUAL(v.front(), cv.front());
        BOOST_CHECK_EQUAL(v.back(), cv.back());

        v.pop_back();
        cv.pop_back();
    }
}

BOOST_AUTO_TEST_CASE(make_heap)
{
    std::vector<int> v {1,2,3,4,5,6,6,7,3};
    auto cv = v;

    std::make_heap(v.begin(), v.end());
    mstd::make_heap(cv.begin(), cv.end());

    while (!v.empty()) {
        mstd::pop_heap(v.begin(), v.end());
        std::pop_heap(cv.begin(), cv.end());

        BOOST_CHECK_EQUAL(v.front(), cv.front());
        BOOST_CHECK_EQUAL(v.back(), cv.back());

        v.pop_back();
        cv.pop_back();
    }

    v = {0, 0, 0, 0};
    cv = v;

    std::make_heap(v.begin(), v.end());
    mstd::make_heap(cv.begin(), cv.end());

    while (!v.empty()) {
        mstd::pop_heap(v.begin(), v.end());
        std::pop_heap(cv.begin(), cv.end());

        BOOST_CHECK_EQUAL(v.front(), cv.front());
        BOOST_CHECK_EQUAL(v.back(), cv.back());

        v.pop_back();
        cv.pop_back();
    }

    v = {8, 9, 1, 3, 12, 5, 10, 3, 1, 100, 3, 23, -1, -33};
    cv = v;

    std::make_heap(v.begin(), v.end());
    mstd::make_heap(cv.begin(), cv.end());

    while (!v.empty()) {
        mstd::pop_heap(v.begin(), v.end());
        std::pop_heap(cv.begin(), cv.end());

        BOOST_CHECK_EQUAL(v.front(), cv.front());
        BOOST_CHECK_EQUAL(v.back(), cv.back());

        v.pop_back();
        cv.pop_back();
    }

}

std::vector<int> heap_sort(const std::initializer_list<int>& l)
{
    std::vector<int> v(l);

    mstd::make_heap(v.begin(), v.end());
    mstd::sort_heap(v.begin(), v.end());

    return v;
}


BOOST_AUTO_TEST_CASE(sort_heap)
{
    auto v = heap_sort({});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));

    v = heap_sort({1});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));

    v = heap_sort({1, 1});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));

    v = heap_sort({2, 4});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));

    v = heap_sort({1, 2, 3});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));

    v = heap_sort({2, 2, 2});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));

    v = heap_sort({10, -1, 3, 33, 22});
    BOOST_REQUIRE(std::is_sorted(v.begin(), v.end()));
}
