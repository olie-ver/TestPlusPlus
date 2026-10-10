#include <testpp/testpp.hpp>

int a = 0;

TEST(Prototype, First) {
    ASSERT_EQ(a, 1);
    a++;
}

TEST(Prototype, Second) {
    ASSERT_EQ(a, 2);
}


TEST(Prototype, Third) {
    ASSERT_EQ(a, 0);
    a++;
}

S_TEST(
    SEQ(Prototype, Third),
    SEQ(Prototype, First),
    SEQ(Prototype, Second)
);