#include <tester/Tests.hpp>

TEST(Passing, ExpectEqual) {
    EXPECT_EQ("hi", "hi");
    EXPECT_EQ(1, 1);

    int a = 5;
    int* b = &a;
    int* c = &a;
    EXPECT_EQ(b, c);
}

TEST(Failing, ExpectEqual) {
    EXPECT_EQ("not", "equal");
    EXPECT_EQ(0, 10000);

    int a = 5;
    int b = 5;
    int* c = &a;
    int* d = &b;
    EXPECT_EQ(c, d);
}

TEST(Passing, ExpectNotEqual) {
    EXPECT_NE("totally", "not equal at all");
    EXPECT_NE(5, 2);

    int a = 5;
    int b = 5;
    int* c = &a;
    int* d = &b;
    EXPECT_NE(c, d);
}

TEST(Failing, ExpectNotEqual) {
    EXPECT_NE("these are equal", "these are equal");
    int a = 5;
    int* b = &a;
    int* c = &a;
    EXPECT_NE(b, c);
}

TEST(Passing, ExpectLessThan) {
    EXPECT_LT(1, 2);

    int a = 5;
    int b = 4;
    int* c = &a;
    int* d = &b;
    EXPECT_LT(d, c);
}

TEST(Failing, ExpectLessThan) {
    EXPECT_LT(2, 1);
    EXPECT_LT(1, 1);

    int a = 5;
    int b = 4;
    int* c = &a;
    int* d = &b;
    EXPECT_LT(c, d);
}

TEST(Passing, ExpectLessThanEqual) {
    EXPECT_LE(2, 2);
    EXPECT_LE(1, 2);
    EXPECT_LE(5.0, 7.9);
}

TEST(Failing, ExpectLessThanEqual) {
    EXPECT_LE(3, 2);
    EXPECT_LE(2, -1);
    EXPECT_LE(80.5, 80.4);
}

TEST(Passing, ExpectGreaterThan) {
    EXPECT_GT(2, 1);
    EXPECT_GT(8000.0, 1);
}

TEST(Failing, ExpectGreaterThan) {
    EXPECT_GT(1, 2);
    EXPECT_GT(-1, 2.0);
}

TEST(Passing, ExpectGreaterThanEqual) {
    EXPECT_GE(1, 1);
    EXPECT_GE(2, 1);
    EXPECT_GE('z', 'c');
}

TEST(Failing, ExpectGreaterThanEqual) {
    EXPECT_GE(0, 1);
    EXPECT_GE(1, 2);
    EXPECT_GE('a', 'b');
}