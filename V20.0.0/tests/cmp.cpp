#include <tester/Tests.hpp>
#include <vector>

/*
----------------------------------------------------------------
    EXPECT_EQ() TESTS
----------------------------------------------------------------
*/

TEST(e_eq, basic) {
    ASSERT_PASSES(EXPECT_EQ(1, 1));
    ASSERT_PASSES(EXPECT_EQ(true, true));
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {1, 2, 3};
    ASSERT_PASSES(EXPECT_EQ(a, a));
    ASSERT_PASSES(EXPECT_EQ(a, b));
}

TEST(e_eq, complicated) {
    ASSERT_PASSES(EXPECT_EQ(true && false, 1 + 0 == 2));
    int a = 5;
    int& b = a;
    ASSERT_PASSES(EXPECT_EQ(a, b));
    ASSERT_PASSES(EXPECT_EQ(&a, &b));

    int* c = &b;
    ASSERT_PASSES(EXPECT_EQ(&a, c));

    const char* str1 = "hi bestie";
    const char* str2 = "hi bestie";

    //passes because the strings are stored in the same place in memory 
    // even though the address of the pointers aren't
    ASSERT_PASSES(EXPECT_EQ(str1, str2)); 
}

TEST(e_eq, fail) {
    for (int i = 0; i < 10; i++) {
        ASSERT_FAILS(EXPECT_EQ(i, (i + 1) * 2));
    }

    ASSERT_FAILS(EXPECT_EQ(5, 10));

    const char* str1 = "hi bestie";
    const char* str2 = "hi bestie";
    //Pointer LOCATIONS are not equal
    ASSERT_FAILS(EXPECT_EQ(&str1, &str2));
}

/*
----------------------------------------------------------------
    EXPECT_NE() TESTS
----------------------------------------------------------------
*/