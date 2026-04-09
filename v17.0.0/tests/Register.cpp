#include <tester/Tests.hpp>
#include <exception>

int hi(int a, int b) {
    a + b;
    throw std::invalid_argument("idk dude");
}

D_TEST(1) {
    EXPECT_THROWS_AS(hi(1, 2), std::bad_alloc);
    // EXPECT_DOES_NOT_THROW(hi(3, 4));

    // EXPECT_THROWS([&] {});
    // EXPECT_DOES_NOT_THROW([&] {throw std::invalid_argument("okay");});
}