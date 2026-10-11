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


int main() {
    for (int i = 0; i < 10; i++) {

    }
}

S_TEST(
    SEQ(Prototype, Third),
    SEQ(Prototype, First),
    SEQ(Prototype, Second)
);