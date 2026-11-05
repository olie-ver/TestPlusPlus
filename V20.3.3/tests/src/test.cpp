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

    // int i = 2;
    // ASSERT_EACH(val, hi, {
    //     ASSERT_NE(i, val);
    //     i++;
    // });

    // ASSERT_WHILE(a, 0, a < 10, {
    //     ASSERT_EQ(a, a);
    //     a++;
    // });


    // auto a = 5; testpp::internal::Assert::assert_while("/Users/oliverlie/Documents/GitHub/TestPlusPlus/V20.3.0/tests/src/test.cpp", 43, [&a](){ a < 10; }, [&]() { })
}

