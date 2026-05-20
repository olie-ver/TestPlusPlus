#include <tester/Tests.hpp>
#include <tester/internal/Core.hpp>
#include <tester/internal/Runner.hpp>
#include <map>
#include <string>
#include <vector>

//These tests are specifically for testing the behavior of 
//  the Assert tests' short-circuiting behavior when they fail within a suite

TEST(assertion_short_circuit, short_circuit) {
    //essentially, have a suite of failing Assert tests
    //  if the Assert test failing causes the test suite to stop evaluating
    //  there will only be one failure in the suite => it works
    ASSERT_TRUE(false); //duh
    ASSERT_FALSE(true);
    ASSERT_EQ(1, 0);
    ASSERT_LT(1, -1);
}

TEST(test_assertion_short_circuit, test) {
    //get the test registry
    std::map<std::string, std::vector<internal::Core::Test>>& REGISTRY = internal::Runner::getRegistry();

    //get the test suite
    std::vector<internal::Core::Test> tests = REGISTRY["assertion_short_circuit"];

    internal::Core::Test test;

    for (auto it = tests.begin(); it != tests.end(); ++it) {
        if (it->name == "short_circuit") {
            test = *it;
            break;
        }
    }

    internal::Core::TestRun testRun;
    internal::Core::TestResult testResult = internal::Runner::runTest("short_circuit", test);

    ASSERT_SIZE(testResult.failures, 1);

    //I could change the code so that the hidden testRun variable is static so I can
    //  manipulate it so that after the above test passes, I remove the failure from 
    //  the previous test and stuff so that if this test doesn't pass, neither does
    //  the other one, but I'm not feeling it so I won't at the moment
}
