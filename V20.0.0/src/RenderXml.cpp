#include <tester/internal/PCH/pch.hpp>

#include <tester/internal/Renderer.hpp>
#include <tester/internal/Escape.hpp>
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

namespace internal::Renderer {

    namespace {

        using TestList = std::vector<Core::TestResult>;

        struct SuiteStats {
            int passed = 0;
            int failed = 0;
            int skipped = 0;
        };

        SuiteStats calculateStats(const TestList& tests) {
            SuiteStats stats;

            for (const auto& test : tests) {
                switch (test.status) {
                    case Core::TestStatus::Passed:
                        stats.passed++;
                        break;

                    case Core::TestStatus::Failed:
                        stats.failed++;
                        break;

                    case Core::TestStatus::Skipped:
                        stats.skipped++;
                        break;
                }
            }

            return stats;
        }

        void renderFailures(std::ostream& stream, const Core::TestResult& test) {
            for (const auto& failure : test.failures) {
                stream << "\t\t\t<failure "
                       << "message=\"" << Helpers::escapeXml(failure.message) << "\" "
                       << "file=\"" << Helpers::escapeXml(failure.file) << "\" "
                       << "line=\"" << failure.line << "\"/>\n";
            }
        }

        void renderTestcase(
            std::ostream& stream,
            const Core::TestResult& test,
            bool includeFailures
        ) {
            const std::string& status = Core::StatusStrings[(int)test.status];

            if (includeFailures && test.status == Core::TestStatus::Failed) {

                stream << "\t\t<testcase "
                       << "name=\"" << Helpers::escapeXml(test.testName) << "\" "
                       << "status=\"" << status << "\">\n";

                renderFailures(stream, test);

                stream << "\t\t</testcase>\n";
            }
            else {
                stream << "\t\t<testcase "
                       << "name=\"" << Helpers::escapeXml(test.testName) << "\" "
                       << "status=\"" << status << "\"/>\n";
            }
        }

        template <typename SuitePredicate, typename TestPredicate>
        void renderXml(
            std::ostream& stream,
            Core::TestRun& testRun,
            SuitePredicate suitePredicate,
            TestPredicate testPredicate,
            bool includeFailures
        ) {
            stream << "<testsuites>\n";

            for (auto&& [suiteName, tests] : testRun.results) {

                SuiteStats stats = calculateStats(tests);

                if (!suitePredicate(suiteName, tests, stats)) {
                    continue;
                }

                stream << "\t<testsuite "
                       << "name=\"" << Helpers::escapeXml(suiteName) << "\" "
                       << "tests=\"" << tests.size() << "\" "
                       << "successes=\"" << stats.passed << "\" "
                       << "failures=\"" << stats.failed << "\" "
                       << "skips=\"" << stats.skipped << "\">\n";

                for (const auto& test : tests) {

                    if (!testPredicate(test)) {
                        continue;
                    }

                    renderTestcase(
                        stream,
                        test,
                        includeFailures
                    );
                }

                stream << "\t</testsuite>\n";
            }

            stream << "</testsuites>";
        }

    }

    void ConsoleRenderer::renderDefaultXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats&) {
                return true;
            },
            [](const Core::TestResult&) {
                return true;
            },
            true
        );
    }

    void ConsoleRenderer::renderMinimumXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats&) {
                return true;
            },
            [](const Core::TestResult&) {
                return true;
            },
            false
        );
    }

    void ConsoleRenderer::renderPassOnlyXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats& stats) {
                return stats.passed > 0;
            },
            [](const Core::TestResult& test) {
                return test.status == Core::TestStatus::Passed;
            },
            false
        );
    }

    void ConsoleRenderer::renderFailAllXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats& stats) {
                return stats.failed > 0;
            },
            [](const Core::TestResult& test) {
                return test.status == Core::TestStatus::Failed;
            },
            true
        );
    }

    void ConsoleRenderer::renderFailMinXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats& stats) {
                return stats.failed > 0;
            },
            [](const Core::TestResult& test) {
                return test.status == Core::TestStatus::Failed;
            },
            false
        );
    }

}