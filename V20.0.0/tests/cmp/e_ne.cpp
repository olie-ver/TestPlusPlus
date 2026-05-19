#include <tester/Tests.hpp>
#include <vector>

TEST(expect_ne, passing) {
    ASSERT_PASSES(EXPECT_NE(1, 0));

    std::vector<int> a = {1, 3, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_PASSES(EXPECT_NE(a, b));
    ASSERT_PASSES(EXPECT_NE(true, false));
}

TEST(expect_ne, failing) {
    ASSERT_FAILS(EXPECT_NE(0, 0));

    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(EXPECT_NE(a, b));
    ASSERT_FAILS(EXPECT_NE(a, a));
}