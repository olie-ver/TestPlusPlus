#include <tester/Tests.hpp>
#include <string>

TEST(Passing, ExpectTrue) {
    EXPECT_TRUE(true);
    EXPECT_TRUE(1 == 1);
    EXPECT_TRUE(std::string("hi") != std::string("bye"));
}

TEST(Failing, ExpectTrue) {
    EXPECT_TRUE(false);
    EXPECT_TRUE(1 == 2);
    EXPECT_TRUE(std::string("what") == std::string("huh"));
}

TEST(Passing, ExpectFalse) {
    EXPECT_FALSE(false);
    EXPECT_FALSE(2 == 1);
    EXPECT_FALSE(std::string("what") == std::string("huh"));
}

TEST(Failing, ExpectFalse) {
    EXPECT_FALSE(true);
    EXPECT_FALSE(1 == 1);
    EXPECT_FALSE(std::string("bye") == std::string("bye"));
}