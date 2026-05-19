#include <tester/Tests.hpp>
#include <vector>

TEST(assert_eq, passing) {
    ASSERT_PASSES(ASSERT_EQ(0, 0));

    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_PASSES(ASSERT_EQ(a, a));
    ASSERT_PASSES(ASSERT_EQ(a, b));
}

TEST(assert_eq, failing) {
    ASSERT_FAILS(ASSERT_EQ(1, 0));

    std::vector<int> a = {1, 3, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(ASSERT_EQ(a, b));

    ASSERT_FAILS(ASSERT_EQ(true, false));
}