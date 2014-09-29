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

    BOOST_REQUIRE(table.begin() == table.cbegin());
    BOOST_REQUIRE(table.end() == table.cend());
}

BOOST_AUTO_TEST_CASE(hash_table_iterators_ops)
{
    mstd::detail::hash_table<int, int> table;

    table.insert_unique(1);
    BOOST_REQUIRE(table.begin() != table.end());
    BOOST_REQUIRE(table.cbegin() != table.cend());

    auto i = table.begin();
    ++i;
    BOOST_REQUIRE(i == table.end());

    table.insert_unique(2);
    table.insert_dup(1);

    auto iter = table.find(1);

    BOOST_REQUIRE_EQUAL(*iter, 1);
    ++iter;
    BOOST_REQUIRE_EQUAL(*iter, 1);
    ++iter;
    if (iter != table.end()) {
        BOOST_REQUIRE_EQUAL(*iter, 2);
    }

    table.insert_dup(2);
    table.insert_dup(2);

    auto cnt = table.count(2);
    BOOST_REQUIRE_EQUAL(cnt, 3);

    auto iters = table.equal_range(2);
    auto first = iters.first;
    BOOST_REQUIRE(first != table.end());
    BOOST_REQUIRE(first != iters.second);
    for (; cnt > 0; ++first, --cnt) {
        BOOST_REQUIRE_EQUAL(*first, 2);
    }
    BOOST_REQUIRE_EQUAL(mstd::distance(iters.first, iters.second), 3);
    BOOST_REQUIRE(first == iters.second);
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

BOOST_AUTO_TEST_CASE(hash_table_lookup_find)
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
}

BOOST_AUTO_TEST_CASE(hash_table_lookup_equal_range)
{
    mstd::detail::hash_table<int, int> table;

    auto list = {1, 3, 4, 2, 9};

    for (auto x : list) {
        table.insert_unique(x);
    }

    for (auto i = 10; i < 100; ++i) {
        table.insert_unique(i);
    }

    for (auto x : list) {
        auto iters = table.equal_range(x);

        BOOST_REQUIRE_EQUAL(table.count(x), 1);

        std::for_each(iters.first, iters.second, [x](int val){
            BOOST_REQUIRE_EQUAL(val, x);
        });

        BOOST_REQUIRE(iters.first != table.end());
        BOOST_REQUIRE_EQUAL(mstd::distance(iters.first, iters.second), 1);
    }
    BOOST_REQUIRE_EQUAL(mstd::distance(table.begin(), table.end()), table.size());

    for (auto x : list) {
        table.insert_dup(x);
    }

    for (auto i = 10; i < 100; ++i) {
        table.insert_dup(i);
    }

    for (auto x : list) {
        auto iters = table.equal_range(x);

        BOOST_REQUIRE_EQUAL(table.count(x), 2);

        std::for_each(iters.first, iters.second, [x](int val){
            BOOST_REQUIRE_EQUAL(val, x);
        });

        BOOST_REQUIRE(iters.first != table.end());
        BOOST_REQUIRE_EQUAL(mstd::distance(iters.first, iters.second), 2);
    }
    BOOST_REQUIRE_EQUAL(mstd::distance(table.begin(), table.end()), table.size());

    {
        table.insert_dup(3);

        auto iters = table.equal_range(3);
        auto cnt = table.count(3);
        BOOST_REQUIRE_EQUAL(cnt, 3);

        std::for_each(iters.first, iters.second, [](int val){
            BOOST_REQUIRE_EQUAL(val, 3);
        });

        BOOST_REQUIRE(iters.first != table.end());
        BOOST_REQUIRE_EQUAL(mstd::distance(iters.first, iters.second), cnt);
    }

    for (auto x : { 0, 5, 7}) {
        auto iters = table.equal_range(x);
        BOOST_REQUIRE(iters.first == iters.second);
        BOOST_REQUIRE(iters.first == table.end());
        BOOST_REQUIRE_EQUAL(table.count(x), 0);
    }

    BOOST_REQUIRE(!table.empty());
    BOOST_REQUIRE_EQUAL(mstd::distance(table.begin(), table.end()), table.size());
}

BOOST_AUTO_TEST_CASE(hash_table_lookup_equal_range_2)
{
    mstd::detail::hash_table<int, int> table;

    auto list = {1, 3, 4, 2, 9};

    for (auto x : list) {
        table.insert_unique(x);
    }

    for (auto i = 10; i < 100; ++i) {
        table.insert_unique(i);
    }

    for (auto x : list) {
        auto iters = table.equal_range(x);

        BOOST_REQUIRE_EQUAL(table.count(x), 1);

        std::for_each(iters.first, iters.second, [x](int val){
            BOOST_REQUIRE_EQUAL(val, x);
        });

        BOOST_REQUIRE(iters.first != table.end());
        BOOST_REQUIRE_EQUAL(mstd::distance(iters.first, iters.second), 1);
    }
    BOOST_REQUIRE_EQUAL(mstd::distance(table.begin(), table.end()), table.size());

    for (auto x : list) {
        table.insert_dup(x);
    }

    for (auto i = 10; i < 100; ++i) {
        table.insert_dup(i);
        table.insert_dup(i);
        table.insert_dup(i);
    }

    for (auto x : list) {
        auto iters = table.equal_range(x);
        auto cnt = table.count(x);

        std::for_each(iters.first, iters.second, [x](int val){
            BOOST_REQUIRE_EQUAL(val, x);
        });

        BOOST_REQUIRE(iters.first != table.end());
        BOOST_REQUIRE_EQUAL(mstd::distance(iters.first, iters.second), cnt);
    }
    BOOST_REQUIRE_EQUAL(mstd::distance(table.begin(), table.end()), table.size());
}

BOOST_AUTO_TEST_CASE(hash_table_lookup_equal_range_3)
{
    mstd::detail::hash_table<int, int> table;

    table.insert_dup(0);
    table.insert_dup(1);
    table.insert_dup(2);
}
