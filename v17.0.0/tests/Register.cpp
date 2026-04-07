#include <tester/Tests.hpp>

D_TEST(3) {
    EXPECT_NEAR(1.0, 2.0, 0.1, 0.1);
    EXPECT_STR_EQ("cool", "not cool");
}

D_TEST(4) {
    EXPECT_STR_EQ("bye", "bye");
    EXPECT_STR_NE("hi", "hi");
}

D_TEST(5) {
    const char first[] = "hihi";
    const char second[] = "hihi";
    const char* p_f = first;
    const char* p_s = second;

    EXPECT_STR_EQ(p_f, p_s);
    EXPECT_STR_NE(p_f, p_s);
}