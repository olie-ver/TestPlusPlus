#include <tester/Tests.hpp>
#include <vector>

TEST(assert_ne, passing) {
    ASSERT_PASSES(ASSERT_NE(1, 0));

    std::vector<int> a = {1, 3, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_PASSES(ASSERT_NE(a, b));
    ASSERT_PASSES(ASSERT_NE(true, false));
}

TEST(assert_ne, failing) {
    ASSERT_FAILS(ASSERT_NE(0, 0));

    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 3};

    ASSERT_FAILS(ASSERT_NE(a, b));
    ASSERT_FAILS(ASSERT_NE(a, a));
}