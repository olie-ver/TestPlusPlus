#include <tester/internal/Renderer.hpp>
#include <tester/internal/Runner.hpp>
#include <fstream>

/* Example xml
    <testsuites>
    <testsuite name="MathTests" tests="2" failures="1">
        <testcase name="AdditionWorks"/>
        <testcase name="DivisionFails">
        <failure message="Expected 4 but got 5"/>
        </testcase>
    </testsuite>
    </testsuites>
*/

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::renderDefaultXml(Core::TestRun& testRun) {
            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
            }
        }

        void ConsoleRenderer::renderMinimumXml(Core::TestRun& result) {
            
        }

        void ConsoleRenderer::renderPassOnlyXml(Core::TestRun& result) {
            
        }

        void ConsoleRenderer::renderFailAllXml(Core::TestRun& result) {
            
        }

        void ConsoleRenderer::renderFailMinXml(Core::TestRun& result) {
            
        }
    }
}