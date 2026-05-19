#include <tester/Tests.hpp>

/*
----------------------------------------------------------------
    EXPECT_TRUE() TESTS
----------------------------------------------------------------
*/

TEST(e_true, basic) {
    ASSERT_PASSES(EXPECT_TRUE(true));
    ASSERT_PASSES(EXPECT_TRUE(1));
    ASSERT_PASSES(EXPECT_TRUE(-1));
}

TEST(e_true, comparison) {
    ASSERT_PASSES(EXPECT_TRUE(1 == 1));
    ASSERT_PASSES(EXPECT_TRUE('h' != 'i'));
    ASSERT_PASSES(EXPECT_TRUE(1 < 2));
    ASSERT_PASSES(EXPECT_TRUE(1 <= 1));
    ASSERT_PASSES(EXPECT_TRUE(2 > -5));
    ASSERT_PASSES(EXPECT_TRUE(0.12 >= 0.1));
}

TEST(e_true, complicated) {
    ASSERT_PASSES(EXPECT_TRUE(1 == 1 && 1 > 0));
    ASSERT_PASSES(EXPECT_TRUE(false || true));
    ASSERT_PASSES(EXPECT_TRUE(7 + 3 == 10 && 5 + 0.3 < 5.300001));
    ASSERT_PASSES(EXPECT_TRUE('a' + 25 == 'z' && 7 - 1 != 0 || 10 / 3 == 3 && 10 % 3 == 1));
}

TEST(e_true, basic_fail) {
    ASSERT_FAILS(EXPECT_TRUE(false));
    ASSERT_FAILS(EXPECT_TRUE(0));
}

TEST(e_true, comparison_fail) {
    ASSERT_FAILS(EXPECT_TRUE(1 != 1));
    ASSERT_FAILS(EXPECT_TRUE('h' == 'i'));
    ASSERT_FAILS(EXPECT_TRUE(1 > 2));
    ASSERT_FAILS(EXPECT_TRUE(1 >= 2));
    ASSERT_FAILS(EXPECT_TRUE(2 < -5));
    ASSERT_FAILS(EXPECT_TRUE(0.12 <= 0.1));
}

//Since these tests passed, then negating them should fail
// YEAH I'M LAZY!! YOU GOTTA PROBLEM WITH THAT?!
TEST(e_true, complicated_fail) {
    ASSERT_FAILS(EXPECT_TRUE(!(1 == 1 && 1 > 0)));
    ASSERT_FAILS(EXPECT_TRUE(!(false || true)));
    ASSERT_FAILS(EXPECT_TRUE(!(7 + 3 == 10 && 5 + 0.3 < 5.300001)));
    ASSERT_FAILS(EXPECT_TRUE(!('a' + 25 == 'z' && 7 - 1 != 0 || 10 / 3 == 3 && 10 % 3 == 1)));
}

/*
----------------------------------------------------------------
    EXPECT_FALSE() TESTS
----------------------------------------------------------------
*/

TEST(e_false, basic) {
    ASSERT_PASSES(EXPECT_FALSE(false));
    ASSERT_PASSES(EXPECT_FALSE(0));
}

TEST(e_false, comparison) {
    ASSERT_PASSES(EXPECT_FALSE(1 != 1));
    ASSERT_PASSES(EXPECT_FALSE(1 == 0));
    ASSERT_PASSES(EXPECT_FALSE(1 > 2));
    ASSERT_PASSES(EXPECT_FALSE(1 >= 5));
    ASSERT_PASSES(EXPECT_FALSE(2 < 0));
    ASSERT_PASSES(EXPECT_FALSE(2 <= -500));
}

TEST(e_false, complicated) {
    ASSERT_PASSES(EXPECT_FALSE(1 != 1 && 2 == 500));
    ASSERT_PASSES(EXPECT_FALSE(!(5 + 10 == 15 || 8 - 1 == 9) && 5 + 5 == 10));
    ASSERT_PASSES(EXPECT_FALSE(true && false));
    ASSERT_PASSES(EXPECT_FALSE(!('h' + 'i')));
}

TEST(e_false, basic_fail) {
    ASSERT_FAILS(EXPECT_FALSE(true));
    ASSERT_FAILS(EXPECT_FALSE(1));
    ASSERT_FAILS(EXPECT_FALSE(-1));
}

TEST(e_false, comparison_fail) {
    ASSERT_FAILS(EXPECT_FALSE(1 == 1));
    ASSERT_FAILS(EXPECT_FALSE('h' != 'i'));
    ASSERT_FAILS(EXPECT_FALSE(1 < 2));
    ASSERT_FAILS(EXPECT_FALSE(1 <= 1));
    ASSERT_FAILS(EXPECT_FALSE(2 > -5));
    ASSERT_FAILS(EXPECT_FALSE(0.12 >= 0.1)); 
}