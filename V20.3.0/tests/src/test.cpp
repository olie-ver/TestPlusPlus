#include <testpp/testpp.hpp>
#include <functional>
#include <vector>

// int a = 0;

// TEST(Prototype, First) {
//     ASSERT_EQ(a, 1);
//     a++;
// }

// TEST(Prototype, Second) {
//     ASSERT_EQ(a, 2);
// }


// TEST(Prototype, Third) {
//     ASSERT_EQ(a, 0);
//     a++;
// }

// S_TEST(
//     SEQ(Prototype, Third),
//     SEQ(Prototype, First),
//     SEQ(Prototype, Second)
// );


D_TEST (test) {
    std::vector<int> hi{1, 2, 3, 4};

    ASSERT_FOR(i, 0, 3, i++, {
        EXPECT_EQ(hi[i], i);
    });

    ASSERT_FALSE(true);
}