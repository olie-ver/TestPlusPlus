#include <tester/Tests.hpp>

TEST(awesome, hi) {
    EXPECT_TRUE(1 == 2);
}

TEST(awesome, hi2) {
    EXPECT_FALSE(2 == 2);
}

D_TEST(we) {
    EXPECT_TRUE(2 == 2);
}

TEST(awesome, hi3) {
    EXPECT_EQ(4, 4);
}

TEST(aweseom, hi) {
    EXPECT_EQ(5, 4);
}

TEST(we, we) {
    std::vector<int> first;
    std::vector<int> second;
    EXPECT_NE(first, second);
}

