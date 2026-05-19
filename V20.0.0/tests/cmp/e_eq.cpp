#include <tester/Tests.hpp>
#include <vector>

TEST(expect_eq, passing) {
    ASSERT_PASSES(EXPECT_EQ(0, 0));

    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_PASSES(EXPECT_EQ(a, a));
    ASSERT_PASSES(EXPECT_EQ(a, b));
}

TEST(expect_eq, failing) {
    ASSERT_FAILS(EXPECT_EQ(1, 0));

    std::vector<int> a = {1, 3, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(EXPECT_EQ(a, b));

    ASSERT_FAILS(EXPECT_EQ(true, false));
}