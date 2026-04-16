#include <tester/Tests.hpp>

void whoo() {
    throw 42;
}

D_TEST(0) {
    EXPECT_THROWS(whoo, float);
}