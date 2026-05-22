#include <tester/internal/Renderer.hpp>
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

namespace internal {
    namespace Renderer {
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

                if (Runner::shouldSkip(suite_name))
                {
                    continue;
                }

                if (!first_suite) {
                    stream << ",\n\t\t";
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
                        stream << ",\n\t\t\t\t";
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
                            stream << ",\n\t\t\t\t\t\t";
                        }

                        first_failure = false;
                        stream << "{\n\t\t\t\t\t\t\t";
                        stream << "\"message\": \"" << test[i].failures[j].message << "\",\n\t\t\t\t\t\t\t";
                        stream << "\"file\": \"" << test[i].failures[j].file << "\",\n\t\t\t\t\t\t\t";
                        stream << "\"line\": \"" << test[i].failures[j].line << "\"\n\t\t\t\t\t\t";
                        stream << "}";
                    }

                    stream << "\n\t\t\t\t\t]\n\t\t\t\t";
                    stream << "}";
                }

                stream << "\n\t\t\t]\n\t\t";
                stream << "}";
            }

            stream << "\n\t]\n";
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
    }
}