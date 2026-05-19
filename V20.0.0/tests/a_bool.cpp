#include <tester/Tests.hpp>
#include <string>
#include <vector>

TEST(assert_true, passing) {
    ASSERT_PASSES(ASSERT_TRUE(true));
    ASSERT_PASSES(ASSERT_TRUE(1 == 1));
    ASSERT_PASSES(ASSERT_TRUE(std::string("hi") == std::string("hi")));
    ASSERT_PASSES(ASSERT_TRUE(std::string("hi") != std::string("bye")));
}

TEST(assert_true, failing) {
    ASSERT_FAILS(ASSERT_TRUE(false));
    ASSERT_FAILS_MSG(ASSERT_TRUE(false), "Expected: false to be true");

    ASSERT_FAILS(ASSERT_TRUE(1 != 1));
    ASSERT_FAILS_MSG(ASSERT_TRUE(1 != 1), "Expected: 1 != 1 to be true");

    ASSERT_FAILS(ASSERT_TRUE(std::string("hi") != std::string("hi")));
    ASSERT_FAILS_MSG(ASSERT_TRUE(std::string("hi") != std::string("hi")), 
        "Expected: std::string(\"hi\") != std::string(\"hi\") to be true");
}

TEST(assert_false, passing) {
    ASSERT_PASSES(ASSERT_FALSE(false));

    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 6};

    ASSERT_PASSES(ASSERT_FALSE(a == b));

    ASSERT_PASSES(ASSERT_FALSE(a != a));
}

TEST(assert_false, failing) {
    ASSERT_FAILS(ASSERT_FALSE(true));
    ASSERT_FAILS_MSG(ASSERT_FALSE(true), "Expected: true to be false");

    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 6};

    ASSERT_FAILS(ASSERT_FALSE(a == a));
    ASSERT_FAILS_MSG(ASSERT_FALSE(a == a), "Expected: a == a to be false");

    ASSERT_FAILS(ASSERT_FALSE(a != b));
    ASSERT_FAILS_MSG(ASSERT_FALSE(a != b), "Expected: a != b to be false");
}