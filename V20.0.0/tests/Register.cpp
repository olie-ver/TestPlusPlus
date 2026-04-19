#include <tester/Tests.hpp>

D_TEST(0) {
    EXPECT_TRUE(false);
    ASSERT_TRUE(false);

    int a = 5;
    int b = 4;
    // std::weak_ordering c = a <=> b;
}