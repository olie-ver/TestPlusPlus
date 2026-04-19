#include <tester/Tests.hpp>

D_TEST(0) {
    char* ptr = nullptr;
    char*& thing = ptr;

    EXPECT_NOT_NULL(thing);
}