#include "../src/TestRunner.hpp"
#include "../src/Tests.hpp"

using namespace TestRunner;
using namespace Tests;

TEST(wazzup, okay) {
    EXPECT_TRUE(1 == 0);
}

TEST(wazzup, alright) {
    EXPECT_TRUE(false);
}