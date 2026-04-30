#include <tester/Tests.hpp>
#include <vector>
#include <unordered_set>
#include <set>

D_TEST(assert_rel_near) {
    // std::vector<int> b = {1, 2, 3, 4, 5};
    // std::vector<int> v = {1, 2, 4, 3, 5};

    // std::unordered_set<int> a = {1, 2, 3, 4, 5};
    // std::unordered_set<int> c = {1, 2, 4, 5, 6};

    // std::set<std::vector<int>> d = {{1, 2, 3}, {4, 5, 6}};
    // std::set<std::vector<int>> e = {{4, 5, 6}, {1, 2, 3}};

    // EXPECT_UNORDERED_EQ(b, v);
    // EXPECT_ORDERED_EQ(a, c);
    // EXPECT_UNORDERED_EQ(d, e);
    // int a[] = {1, 2, 3, 4, 5};
    // int b[] = {1, 2, 3, 4, 5};

    // EXPECT_UNORDERED_EQ(a, b);

    std::set<std::vector<int>> a = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> b = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_ORDERED_EQ(a, b);
}