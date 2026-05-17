#include <tester/Tests.hpp>
#include <vector>
#include <unordered_set>
#include <set>

D_TEST(assert_rel_near) {
    // EXPECT_PASSES(EXPECT_FALSE(true));
    EXPECT_PASSES(ASSERT_TRUE(false));
}