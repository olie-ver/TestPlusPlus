#include <tester/internal/Renderer.hpp>
#include <tester/internal/Runner.hpp>
#include <cstdio>
#include <iostream>
#include <map>
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

       /* Example json
            {
                suites: [
                    {
                        suite_name: name,
                        tests: [
                            {
                                suiteName: name,
                                testName: test,
                                status: status,
                                durationMs: durationMs,
                                failures: [
                                    {
                                        message: message,
                                        file: file,
                                        line: line
                                    }
                                ]
                            },
                        ]
                    }
                ]
            }
       */


        void ConsoleRenderer::renderDefaultJson(Core::TestRun& testRun) {
            std::fstream stream;
            stream.open(jsonFile, std::fstream::out);

            auto& tests = testRun.results;

            stream << "{\n\t\"suites\": [\n\t\t";

            auto& skip = Runner::getSkipSuites();
            auto& testOnly = Runner::getTestOnly();

            bool first_suite = true;

            for (auto it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;

                if (skip.contains(suite_name) 
                    || (testOnly.size() != 0 && !testOnly.contains(suite_name)))
                {
                    continue;
                }

                if (!first_suite) {
                    stream << "\t,";
                }

                first_suite = false;

                bool first_test = true;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();

                stream << "{\n\t\t\t";
                stream << "\"suite_name\": \"" << suite_name << "\",\n\t\t\t";
                stream << "\"tests\": [\n\t\t\t\t";

                for (size_t i = 0; i < size; i++) {
                    if (!first_test) {
                        stream << "\t,";
                    }

                    first_test = false;

                    stream << "{\n\t\t\t\t\t";
                    stream << "\"suiteName\": \"" << suite_name << "\",\n\t\t\t\t\t";
                    stream << "\"testName\": \"" << test[i].testName << "\",\n\t\t\t\t\t";
                    stream << "\"status\": \"" << Core::StatusStrings[(int)test[i].status] << "\",\n\t\t\t\t\t";
                    stream << "\"durationMs\": \"" << test[i].durationMs << "\",\n\t\t\t\t\t";
                    stream << "\"failures\": [\n\t\t\t\t\t\t";

                    size_t num_failures = test[i].failures.size();

                    bool first_failure = true;
                    for (size_t j = 0; j < num_failures; j++) {
                        if (!first_failure) {
                            stream << "\t,";
                        }

                        first_failure = false;
                        stream << "{\n\t\t\t\t\t\t\t";
                        stream << "\"message\": \"" << test[i].failures[j].message << "\",\n\t\t\t\t\t\t\t";
                        stream << "\"file\": \"" << test[i].failures[j].file << "\",\n\t\t\t\t\t\t\t";
                        stream << "\"line\": \"" << test[i].failures[j].line << "\"\n\t\t\t\t\t\t";
                        stream << "}\n\t\t\t\t\t";
                    }

                    stream << "]\n\t\t\t\t";
                    stream << "}\n\t\t\t";
                }

                stream << "]\n\t\t";
                stream << "}\n\t";
            }

            stream << "]\n";
            stream << "}";
        }

        void ConsoleRenderer::renderMinimumJson(Core::TestRun& result) {
            
        }

        void ConsoleRenderer::renderPassOnlyJson(Core::TestRun& result) {
            
        }

        void ConsoleRenderer::renderFailAllJson(Core::TestRun& result) {
            
        }

        void ConsoleRenderer::renderFailMinJson(Core::TestRun& result) {
            
        }

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

        void ConsoleRenderer::renderDefault(Core::TestRun& testRun) {
            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];

                    switch (result.status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::Failure& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }
                            testRun.failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " << result.testName << std::endl;
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderMinimum(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];

                    switch (result.status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " << result.testName << std::endl;
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderPassOnly(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.status) {
                        case Core::TestStatus::Passed: 
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.passed++;
                            break;
                        case Core::TestStatus::Failed:
                            testRun.failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderFailAll(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.status) {
                        case Core::TestStatus::Passed: 
                            testRun.passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::Failure& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }
                            testRun.failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderFailMin(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.status) {
                        case Core::TestStatus::Passed: 
                            testRun.passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }
    }
}