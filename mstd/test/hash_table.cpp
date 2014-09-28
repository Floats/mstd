#include <boost/test/unit_test.hpp>
#include <mstd/container/hash/hash_table.hpp>

BOOST_AUTO_TEST_CASE(hash_table_base)
{
    mstd::detail::hash_table<int, int> table;

    BOOST_REQUIRE_EQUAL(table.size(), 0);
    BOOST_REQUIRE(table.empty());
}

BOOST_AUTO_TEST_CASE(hash_table_iterators)
{
    mstd::detail::hash_table<int, int> table;
    const auto& ctable = table;

    BOOST_REQUIRE(table.begin() == table.end());
    BOOST_REQUIRE(table.cbegin() == table.cend());
    BOOST_REQUIRE(ctable.begin() == ctable.end());
    BOOST_REQUIRE(ctable.cbegin() == ctable.cend());
}

BOOST_AUTO_TEST_CASE(hash_table_insert_1)
{
    mstd::detail::hash_table<int, int> table;
    BOOST_REQUIRE(table.empty());

    table.insert_unique(0);
    BOOST_REQUIRE_EQUAL(table.size(), 1);
    BOOST_REQUIRE(!table.empty());

    auto list = {1, 2, 3, 4, 5, 6};

    for (auto x : list) {
        auto iter = table.insert_unique(x);

        BOOST_REQUIRE(iter.first != table.end());
        BOOST_REQUIRE_EQUAL(*iter.first, x);
        BOOST_REQUIRE(iter.second);
    }

    BOOST_REQUIRE_EQUAL(table.size(), list.size() + 1);
    BOOST_REQUIRE(!table.empty());
}

BOOST_AUTO_TEST_CASE(hash_table_insert)
{
    mstd::detail::hash_table<int, int> table;

    for (auto x : {1,2,3,4,5}) {
        auto iter = table.insert_unique(x);

        BOOST_REQUIRE_EQUAL(*iter.first, x);
        BOOST_REQUIRE(iter.second);
    }
    BOOST_REQUIRE_EQUAL(table.size(), 5);
    BOOST_REQUIRE(!table.empty());

    for (auto x : {1,2,3,4,5}) {
        auto iter = table.insert_unique(x);

        BOOST_REQUIRE_EQUAL(*iter.first, x);
        BOOST_REQUIRE(!iter.second);
    }
    BOOST_REQUIRE_EQUAL(table.size(), 5);
    BOOST_REQUIRE(!table.empty());

    for (auto x : {1,2,3,4,5}) {
        auto iter = table.insert_dup(x);

        BOOST_REQUIRE_EQUAL(*iter, x);
    }
    BOOST_REQUIRE_EQUAL(table.size(), 10);
    BOOST_REQUIRE(!table.empty());
}

BOOST_AUTO_TEST_CASE(hash_table_lookup)
{
    mstd::detail::hash_table<int, int> table;

    auto list = {1, 3, 4, 2, 9};

    for (auto x : list) {
        table.insert_unique(x);
    }

    for (auto x : list) {
        auto iter = table.find(x);
        BOOST_REQUIRE_EQUAL(*iter, x);
        BOOST_REQUIRE(iter != table.end());
    }


    for (auto x : { 0, 5, 7}) {
        BOOST_REQUIRE(table.find(x) == table.end());
    }

    for (auto x : list) {
        auto iters = table.equal_range(x);

        BOOST_REQUIRE_EQUAL(table.count(x), 1);
        BOOST_REQUIRE(iters.first != table.end());
        BOOST_REQUIRE(mstd::distance(iters.first, iters.second) == 1);
    }

    for (auto x : { 0, 5, 7}) {
        auto iters = table.equal_range(x);
        BOOST_REQUIRE(iters.first == iters.second);
        BOOST_REQUIRE(iters.first == table.end());
        BOOST_REQUIRE_EQUAL(table.count(x), 0);
    }

    BOOST_REQUIRE(!table.empty());
}
