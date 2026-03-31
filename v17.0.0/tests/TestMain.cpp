#include "TestCore.hpp"
#include "Renderer.hpp"
#include "Tests.hpp"
#include "TestRunner.hpp"

using namespace TestCore;
using namespace TestRunner;
using namespace TestResultRenderer;
using namespace Tests;

int main(int argc, char** argv) {
    TestRunResult mockRun;

    TestResult result = runTest("MathTests", "BasicFail", []() {
        EXPECT_TRUE(1 == 2);
    });

    TestResult result2 = runTest("AnotherTest", "BasicFail", []() {
        EXPECT_TRUE(2 == 2);
    });

    mockRun.tests = { result, result2 };

    ConsoleRenderer renderer;

    renderer.render(mockRun);
    return EXIT_SUCCESS;
}