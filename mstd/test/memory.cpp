#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <mstd/memory/allocator.hpp>

struct TestT {
    int x;

    TestT() noexcept : x(10) {}
    TestT(const TestT& v) noexcept : x(v.x) {}
    TestT(int, int t) noexcept : x(t) {}

    ~TestT() { x = 0; }

    TestT* operator&() const noexcept
    {
        return nullptr;
    }
};

inline bool operator==(TestT x, TestT y) noexcept
{
    return x.x == y.x;
}

BOOST_AUTO_TEST_CASE(alloctor_int)
{
    mstd::allocator<int> alloc;

    auto p = alloc.allocate(10);

    BOOST_REQUIRE(!std::all_of(p, p + 10, [](int x){ return x == 0; }));

    std::fill_n(p, 10, 100);
    BOOST_REQUIRE_EQUAL(std::count(p, p + 10, 100), 10);

    BOOST_REQUIRE_EQUAL(alloc.address(*p), p);
    BOOST_REQUIRE_EQUAL(alloc.address(*(p + 1)), p + 1);

    alloc.deallocate(p);
}

BOOST_AUTO_TEST_CASE(allocator_class)
{
    mstd::allocator<TestT> alloc;

    auto x = alloc.allocate(1);

    BOOST_REQUIRE(x);
    BOOST_CHECK_NE(x->x, 10);

    alloc.construct(x);
    BOOST_CHECK_EQUAL(x->x, 10);

    alloc.destroy(x);
    BOOST_CHECK_EQUAL(x->x, 0);

    for (auto t: {3, 4, 5, 6}) {
        alloc.construct(x, 0, t);
        BOOST_CHECK_EQUAL(x->x, t);

        alloc.destroy(x);
        BOOST_CHECK_EQUAL(x->x, 0);
    }

    TestT cp{0, 100};
    alloc.construct(x, cp);
    BOOST_CHECK_EQUAL(x->x, 100);

    BOOST_REQUIRE_EQUAL(&cp, static_cast<TestT*>(nullptr));

    BOOST_REQUIRE_EQUAL(x, alloc.address(*x));

    alloc.deallocate(x);
}

BOOST_AUTO_TEST_CASE(construct)
{
    mstd::allocator<int> alloc;

    constexpr auto sz = 10;
    constexpr auto val = 3;

    auto p = alloc.allocate(sz);

    std::fill_n(p, sz, val);
    BOOST_REQUIRE_EQUAL(std::count(p, p + sz, val), sz);

    mstd::destroy(p, p + sz);
    BOOST_REQUIRE_EQUAL(std::count(p, p + sz, val), sz);

    alloc.deallocate(p);

    mstd::allocator<TestT> alloc2;
    auto q = alloc2.allocate(sz);
    std::uninitialized_fill_n(q, sz, TestT{});

    BOOST_REQUIRE_EQUAL(std::count(q, q + sz, TestT{}), sz);

    mstd::destroy(q, q + sz);
    BOOST_REQUIRE_EQUAL(std::count(q, q + sz, TestT{0, 0}), sz);

    alloc2.deallocate(q);
}
