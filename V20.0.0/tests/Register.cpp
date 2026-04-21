#include <tester/Tests.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

TEST(expect_throws, no_exception_type) {
    EXPECT_THROWS(dumbFunc(5, 10), float);
}