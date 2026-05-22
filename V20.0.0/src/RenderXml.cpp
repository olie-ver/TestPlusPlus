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
            std::fstream stream;
            stream.open(junitFile, std::fstream::out);

            stream << "<testsuites>\n";

            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();

                int numPassed = 0;
                int numFailed = 0;
                int numSkipped = 0;

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            numPassed++;
                            break;

                        case Core::TestStatus::Skipped:
                            numSkipped++;
                            break;

                        case Core::TestStatus::Failed:
                            numFailed++;
                            break;
                    }
                }

                stream << "\t<testsuite name=\"" << suite_name << "\" tests=\""
                    << size << "\" successes=\"" << numPassed << "\" failures=\"" << numFailed 
                    << "\" skips=\"" << numSkipped << "\">\n";

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"passed\"/>\n";
                            break;

                        case Core::TestStatus::Skipped:
                            stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"skipped\"/>\n";
                            break;

                        case Core::TestStatus::Failed:
                            stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"failed\">\n";
                            size_t numFailures = test[i].failures.size();

                            for (size_t j = 0; j < numFailures; j++) {
                                stream << "\t\t\t<failure message=\"" << test[i].failures[j].message << "\"/>\n";
                            }
                            stream << "\t\t</testcase>\n";
                            break;
                    }
                }

                stream << "\t</testsuite>\n";
            }
            stream << "</testsuites>";
        }

        void ConsoleRenderer::renderMinimumXml(Core::TestRun& testRun) {
            std::fstream stream;
            stream.open(junitFile, std::fstream::out);

            stream << "<testsuites>\n";

            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();

                int numPassed = 0;
                int numFailed = 0;
                int numSkipped = 0;

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            numPassed++;
                            break;
                            
                        case Core::TestStatus::Skipped:
                            numSkipped++;
                            break;

                        case Core::TestStatus::Failed:
                            numFailed++;
                            break;
                    }
                }

                stream << "\t<testsuite name=\"" << suite_name << "\" tests=\""
                    << size << "\" successes=\"" << numPassed << "\" failures=\"" << numFailed 
                    << "\" skips=\"" << numSkipped << "\">\n";

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"passed\"/>\n";
                            break;

                        case Core::TestStatus::Skipped:
                            stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"skipped\"/>\n";
                            break;

                        case Core::TestStatus::Failed:
                            stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"failed\"/>\n";
                            break;
                    }
                }

                stream << "\t</testsuite>\n";
            }
            stream << "</testsuites>";
        }

        void ConsoleRenderer::renderPassOnlyXml(Core::TestRun& testRun) {
            std::fstream stream;
            stream.open(junitFile, std::fstream::out);

            stream << "<testsuites>\n";

            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();

                int numPassed = 0;
                int numFailed = 0;
                int numSkipped = 0;

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            numPassed++;
                            break;
                            
                        case Core::TestStatus::Skipped:
                            numSkipped++;
                            break;

                        case Core::TestStatus::Failed:
                            numFailed++;
                            break;
                    }
                }

                if (numPassed == 0) {
                    continue;
                }

                stream << "\t<testsuite name=\"" << suite_name << "\" tests=\""
                    << size << "\" successes=\"" << numPassed << "\" failures=\"" << numFailed 
                    << "\" skips=\"" << numSkipped << "\">\n";

                for (size_t i = 0; i < size; i++) {
                    if (test[i].status == Core::TestStatus::Passed) {
                        stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"passed\"/>\n";
                    }
                }

                stream << "\t</testsuite>\n";
            }
            stream << "</testsuites>";
        }

        void ConsoleRenderer::renderFailAllXml(Core::TestRun& testRun) {
            std::fstream stream;
            stream.open(junitFile, std::fstream::out);

            stream << "<testsuites>\n";

            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();

                int numPassed = 0;
                int numFailed = 0;
                int numSkipped = 0;

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            numPassed++;
                            break;

                        case Core::TestStatus::Skipped:
                            numSkipped++;
                            break;

                        case Core::TestStatus::Failed:
                            numFailed++;
                            break;
                    }
                }

                if (numFailed == 0) {
                    continue;
                }

                stream << "\t<testsuite name=\"" << suite_name << "\" tests=\""
                    << size << "\" successes=\"" << numPassed << "\" failures=\"" << numFailed 
                    << "\" skips=\"" << numSkipped << "\">\n";

                for (size_t i = 0; i < size; i++) {
                    if (test[i].status == Core::TestStatus::Failed) {
                        stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"failed\">\n";
                        size_t numFailures = test[i].failures.size();

                        for (size_t j = 0; j < numFailures; j++) {
                            stream << "\t\t\t<failure message=\"" << test[i].failures[j].message << "\"/>\n";
                        }
                        stream << "\t\t</testcase>\n";
                    }
                }

                stream << "\t</testsuite>\n";
            }
            stream << "</testsuites>";
        }

        void ConsoleRenderer::renderFailMinXml(Core::TestRun& testRun) {
            std::fstream stream;
            stream.open(junitFile, std::fstream::out);

            stream << "<testsuites>\n";

            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) {
                const std::string& suite_name = it->first;
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();

                int numPassed = 0;
                int numFailed = 0;
                int numSkipped = 0;

                for (size_t i = 0; i < size; i++) {
                    switch (test[i].status) {
                        case Core::TestStatus::Passed:
                            numPassed++;
                            break;

                        case Core::TestStatus::Skipped:
                            numSkipped++;
                            break;

                        case Core::TestStatus::Failed:
                            numFailed++;
                            break;
                    }
                }

                if (numFailed == 0) {
                    continue;
                }

                stream << "\t<testsuite name=\"" << suite_name << "\" tests=\""
                    << size << "\" successes=\"" << numPassed << "\" failures=\"" << numFailed 
                    << "\" skips=\"" << numSkipped << "\">\n";

                for (size_t i = 0; i < size; i++) {
                    if (test[i].status == Core::TestStatus::Failed) {
                        stream << "\t\t<testcase name=\"" << test[i].testName << "\" status=\"failed\"/>\n";
                    }
                }

                stream << "\t</testsuite>\n";
            }
            stream << "</testsuites>";
        }
    }
}