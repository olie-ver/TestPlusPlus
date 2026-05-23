#include <tester/internal/Renderer.hpp>
#include <tester/internal/Escape.hpp>
#include <tester/internal/Runner.hpp>
#include <fstream>

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

namespace internal::Renderer {
    namespace {
        using TestList = std::vector<Core::TestResult>;

        bool hasStatus(const TestList& tests, Core::TestStatus status) {
            for (const auto& test : tests) {
                if (test.status == status) {
                    return true;
                }
            }

            return false;
        }

        void renderFailures(std::fstream& stream, const Core::TestResult& test) {
            stream << "[\n\t\t\t\t\t\t";

            bool first = true;

            for (const auto& failure : test.failures) {
                if (!first) {
                    stream << ",\n\t\t\t\t\t\t";
                }

                first = false;

                stream << "{\n\t\t\t\t\t\t\t";
                stream << "\"message\": \"" << Helpers::escapeJson(failure.message) << "\",\n\t\t\t\t\t\t\t";
                stream << "\"file\": \"" << Helpers::escapeJson(failure.file) << "\",\n\t\t\t\t\t\t\t";
                stream << "\"line\": \"" << failure.line << "\"\n\t\t\t\t\t\t";
                stream << "}";
            }

            stream << "\n\t\t\t\t\t]";
        }

        void renderTest(
            std::fstream& stream,
            const std::string& suiteName,
            const Core::TestResult& test,
            bool includeFailures
        ) {
            stream << "{\n\t\t\t\t\t";
            stream << "\"suiteName\": \"" << Helpers::escapeJson(suiteName) << "\",\n\t\t\t\t\t";
            stream << "\"testName\": \"" << Helpers::escapeJson(test.testName) << "\",\n\t\t\t\t\t";
            stream << "\"status\": \"" << Core::StatusStrings[(int)test.status] << "\",\n\t\t\t\t\t";
            stream << "\"durationMs\": \"" << test.durationMs << "\",\n\t\t\t\t\t";
            stream << "\"failures\": ";

            if (includeFailures) {
                renderFailures(stream, test);
            }
            else {
                stream << "[]";
            }

            stream << "\n\t\t\t\t}";
        }

        template <typename SuitePredicate, typename TestPredicate>
        void renderJson(
            std::fstream& stream,
            Core::TestRun& testRun,
            SuitePredicate suitePredicate,
            TestPredicate testPredicate,
            bool includeFailures
        ) {
            stream << "{\n\t\"suites\": [\n\t\t";

            bool firstSuite = true;

            for (auto&& [suiteName, tests] : testRun.results) {

                if (!suitePredicate(suiteName, tests)) {
                    continue;
                }

                if (!firstSuite) {
                    stream << ",\n\t\t";
                }

                firstSuite = false;

                stream << "{\n\t\t\t";
                stream << "\"suite_name\": \"" << Helpers::escapeJson(suiteName) << "\",\n\t\t\t";
                stream << "\"tests\": [\n\t\t\t\t";

                bool firstTest = true;

                for (const auto& test : tests) {

                    if (!testPredicate(test)) {
                        continue;
                    }

                    if (!firstTest) {
                        stream << ",\n\t\t\t\t";
                    }

                    firstTest = false;

                    renderTest(stream, suiteName, test, includeFailures);
                }

                stream << "\n\t\t\t]\n\t\t";
                stream << "}";
            }

            stream << "\n\t]\n}";
        }

    }

    void ConsoleRenderer::renderDefaultJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList&) {
                return !Runner::shouldSkip(suite);
            },
            [](const Core::TestResult&) {
                return true;
            },
            true
        );
    }

    void ConsoleRenderer::renderMinimumJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList&) {
                return !Runner::shouldSkip(suite);
            },
            [](const Core::TestResult&) {
                return true;
            },
            false
        );
    }

    void ConsoleRenderer::renderPassOnlyJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList& tests) {
                return !Runner::shouldSkip(suite)
                    && hasStatus(tests, Core::TestStatus::Passed);
            },
            [](const Core::TestResult& test) {
                return test.status == Core::TestStatus::Passed;
            },
            false
        );
    }

    void ConsoleRenderer::renderFailAllJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList& tests) {
                return !Runner::shouldSkip(suite)
                    && hasStatus(tests, Core::TestStatus::Failed);
            },
            [](const Core::TestResult& test) {
                return test.status == Core::TestStatus::Failed;
            },
            true
        );
    }

    void ConsoleRenderer::renderFailMinJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList& tests) {
                return !Runner::shouldSkip(suite)
                    && hasStatus(tests, Core::TestStatus::Failed);
            },
            [](const Core::TestResult& test) {
                return test.status == Core::TestStatus::Failed;
            },
            false
        );
    }
}