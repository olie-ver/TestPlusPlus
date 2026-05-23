#include <tester/internal/PCH/pch.hpp>

#include <tester/internal/Renderer.hpp>
#include <iostream>

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::render(Core::TestRun& testRun) 
        {

            if (jsonFile != "") {
                switch (verb) {
                    case Core::Verbosity::Default:
                        renderDefaultJson(testRun);
                        break;
                    case Core::Verbosity::Minimum:
                        renderMinimumJson(testRun);
                        break;
                    case Core::Verbosity::PassOnly:
                        renderPassOnlyJson(testRun);
                        break;
                    case Core::Verbosity::FailOnlyMin:
                        renderFailMinJson(testRun);
                        break;
                    case Core::Verbosity::FailOnlyAll:
                        renderFailAllJson(testRun);
                        break;
                }
            }

            if (junitFile != "") {
                switch (verb) {
                    case Core::Verbosity::Default:
                        renderDefaultXml(testRun);
                        break;
                    case Core::Verbosity::Minimum:
                        renderMinimumXml(testRun);
                        break;
                    case Core::Verbosity::PassOnly:
                        renderPassOnlyXml(testRun);
                        break;
                    case Core::Verbosity::FailOnlyMin:
                        renderFailMinXml(testRun);
                        break;
                    case Core::Verbosity::FailOnlyAll:
                        renderFailAllXml(testRun);
                        break;
                }
            }

            if (jsonFile != "" || junitFile != "") {
                return;
            }

            std::cout << "Running " << testRun.total << " tests..." << std::endl;
 
            std::cout << std::endl;

            switch (verb) {
                case Core::Verbosity::Default:
                    renderDefault(testRun);
                    break;
                case Core::Verbosity::Minimum:
                    renderMinimum(testRun);
                    break;
                case Core::Verbosity::PassOnly:
                    renderPassOnly(testRun);
                    break;
                case Core::Verbosity::FailOnlyMin:
                    renderFailMin(testRun);
                    break;
                case Core::Verbosity::FailOnlyAll:
                    renderFailAll(testRun);
                    break;
            }

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Total: " << testRun.total;
            std::cout << " | Passed: " << testRun.passed;
            std::cout << " | Failed: " << testRun.failed;
            std::cout << " | Skipped: " << testRun.skipped << std::endl;
            std::cout << "Time: " << testRun.totalMs << " ms" << std::endl;
        }
    }
}