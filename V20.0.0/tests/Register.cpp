#include <tester/Tests.hpp>
#include <string>
#include <iostream>

#include <tester/Tests.hpp>


D_TEST(0) {
    char a[] = {'a'};
    char b[] = {'b'};
    EXPECT_STR_EQ(a, b);

    char c[] = {'a', '\0'};
    char d[] = {'a', '\0', '\0'};
    EXPECT_STR_EQ(a, c);
    EXPECT_STR_EQ(c, d);

    char e[] = {'a', 'b'};
    EXPECT_STR_EQ(c, e);

    char f[] = {'a', 'b'};
    EXPECT_STR_EQ(a, f);
}