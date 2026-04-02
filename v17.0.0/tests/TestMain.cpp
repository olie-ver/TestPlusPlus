#include "TestCore.hpp"
#include "Renderer.hpp"
#include "Tests.hpp"
#include "TestRunner.hpp"

using namespace TestCore;
using namespace TestRunner;
using namespace TestResultRenderer;
using namespace Tests;

// TEST(hi, again) {
//     EXPECT_TRUE(1 == 2);
// }

// D_TEST(hi) {
//     EXPECT_TRUE(2 == 2);
// }

int main() {
    TestRunResult mockRun;

    runAllRegisteredTests(mockRun);

    ConsoleRenderer renderer;

    renderer.render(mockRun);
    return EXIT_SUCCESS;
}