#include <tester/Tests.hpp>
#include <string>
#include <vector>

TEST(expect_true, passing) {
    ASSERT_PASSES(EXPECT_TRUE(true));
    ASSERT_PASSES(EXPECT_TRUE(1 == 1));
    ASSERT_PASSES(EXPECT_TRUE(std::string("hi") == std::string("hi")));
    ASSERT_PASSES(EXPECT_TRUE(std::string("hi") != std::string("bye")));
}

TEST(expect_true, failing) {
    ASSERT_FAILS(EXPECT_TRUE(false));
    ASSERT_FAILS_MSG(EXPECT_TRUE(false), "Expected: false to be true");

    ASSERT_FAILS(EXPECT_TRUE(1 != 1));
    ASSERT_FAILS_MSG(EXPECT_TRUE(1 != 1), "Expected: 1 != 1 to be true");

    ASSERT_FAILS(EXPECT_TRUE(std::string("hi") != std::string("hi")));
    ASSERT_FAILS_MSG(EXPECT_TRUE(std::string("hi") != std::string("hi")), 
        "Expected: std::string(\"hi\") != std::string(\"hi\") to be true");
}

TEST(expect_false, passing) {
    ASSERT_PASSES(EXPECT_FALSE(false));

    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 6};

    ASSERT_PASSES(EXPECT_FALSE(a == b));

    ASSERT_PASSES(EXPECT_FALSE(a != a));
}

TEST(expect_false, failing) {
    ASSERT_FAILS(EXPECT_FALSE(true));
    ASSERT_FAILS_MSG(EXPECT_FALSE(true), "Expected: true to be false");

    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 6};

    ASSERT_FAILS(EXPECT_FALSE(a == a));
    ASSERT_FAILS_MSG(EXPECT_FALSE(a == a), "Expected: a == a to be false");

    ASSERT_FAILS(EXPECT_FALSE(a != b));
    ASSERT_FAILS_MSG(EXPECT_FALSE(a != b), "Expected: a != b to be false");
}