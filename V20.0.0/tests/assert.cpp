#include <tester/Tests.hpp>
#include <tester/internal/Core.hpp>
#include <tester/internal/Runner.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>

//Try this out for meta testing behavior
// Core::Test temp;
// temp.suite_name = "__internal";
// temp.test_name = "assert_short_circuit";

// temp.test = []() {
//     ASSERT_TRUE(false);
//     ASSERT_FALSE(true);
// };

// auto result = Runner::runTest(temp);

//These tests are specifically for testing the behavior of 
//  the Assert tests' short-circuiting behavior when they fail within a suite

// TEST(assertion_short_circuit, short_circuit) {
//     //essentially, have a suite of failing Assert tests
//     //  if the Assert test failing causes the test suite to stop evaluating
//     //  there will only be one failure in the suite => it works
//     ASSERT_TRUE(false); //duh
//     ASSERT_FALSE(true);
//     ASSERT_EQ(1, 0);
//     ASSERT_LT(1, -1);
// }

// TEST(test_assertion_short_circuit, test) {
    //get the test registry
    // std::vector<internal::Core::Test>& REGISTRY = internal::Runner::getRegistry();

    //get the test suite
    // std::vector<internal::Core::Test> tests = REGISTRY["assertion_short_circuit"];

    // internal::Core::Test test;

    // for (auto it = REGISTRY.begin(); it != REGISTRY.end(); ++it) {
    //     if (it->suite_name == "assertion_short_circuit") {
    //         if (it->test_name == "short_circuit") {
    //             test = *it;
    //             break;
    //         }
    //     }
    // }

    // internal::Core::TestRun testRun;
    // internal::Core::TestResult testResult = internal::Runner::runTest(test);

    // std::cout << "//////////////////" << testResult.failures.size() <<  "//////////////////" << std::endl;
    // if (testResult.status == internal::Core::TestStatus::Passed) {
    //     std::cout << "//////////////////" << " PASSED " <<  "//////////////////" << std::endl;
    // } else if (testResult.status == internal::Core::TestStatus::Failed) {
    //     std::cout << "//////////////////" << " FAILED " <<  "//////////////////" << std::endl;
    // }

    // ASSERT_SIZE(testResult.failures, 1);
    // ASSERT_EQ(0, 0);

    // std::cout << "//////////////////" << testResult.failures.size() <<  "//////////////////" << std::endl;
    //If the ASSERT fails, the code ahead won't run
    //  so if this test passes, then the failure of the other test will be cleared
    //  but if this test fails, then the failure of the other test won't be cleared
    //  so either both fail or both pass

    //grab the test run
    // internal::Core::TestRun& globalRun = internal::Runner::makeTestRun();
    // std::cout << "//////////////////" << "GOT TEST RUN" <<  "//////////////////" << std::endl;
    //grab the suite with the failing test
    // std::vector<internal::Core::TestResult>& results = globalRun.results["assertion_short_circuit"];
    // std::cout << "//////////////////" << "GRABBED RESULTS" <<  "//////////////////" << std::endl;
    //remove its failures
    // results[0].failures.clear();
    // std::cout << "//////////////////" << "REMOVED FAILURES" <<  "//////////////////" << std::endl;
    //change its status to passed
    // results[0].status = internal::Core::TestStatus::Passed;
// }
