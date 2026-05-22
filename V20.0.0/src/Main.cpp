#include <tester/internal/Core.hpp>
#include <tester/internal/Renderer.hpp>
#include <tester/internal/Runner.hpp>
#include <tester/internal/Main.hpp>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    int num_threads = 1;
    int timeout = 0;

    internal::Core::Verbosity verbFlag = internal::Core::Verbosity::Default;
    internal::Core::TimeUnit unit = internal::Core::TimeUnit::Seconds;
    auto& skipSuites = internal::Runner::getSkipSuites();
    auto& testOnlySuites = internal::Runner::getTestOnly();

    std::string jsonFile = "";
    std::string jUnitFile = "";

    // process the arguments
    for (int i = 1; i < argc; i++) {
        std::string flag(argv[i]);
        std::transform(flag.begin(), flag.end(), flag.begin(), 
            [](unsigned char c) { return std::tolower(c); });

        if (flag.find("--v=") != std::string::npos 
            || flag.find("--verbosity=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);
            verbFlag = getVerbFlag(arg);
        } else if (flag.find("--num_threads=") != std::string::npos
            || flag.find("--threads=") != std::string::npos
            || flag.find("--t=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);

            try {
                num_threads = getNumThreads(arg);
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        } else if (flag.find("--s=") != std::string::npos 
            || flag.find("--skip=") != std::string::npos)
        {
            std::string originalFlag(argv[i]);
            std::string arg = originalFlag.substr(originalFlag.find('=') + 1);
            getSkip(arg, skipSuites);
        } else if (flag.find("--testonly=") != std::string::npos
            || flag.find("--test_only=") != std::string::npos
            || flag.find("--t_o=") != std::string::npos 
            || flag.find("--to=") != std::string::npos)
        {
            std::string originalFlag(argv[i]);
            std::string arg = originalFlag.substr(originalFlag.find('=') + 1);
            getTestOnly(arg, testOnlySuites);
        } else if (flag.find("--timeout") != std::string::npos 
            && flag.find('=') != std::string::npos)
        {
            if (flag.find("_ms=") != std::string::npos) {
                unit = internal::Core::TimeUnit::Milliseconds;
            }

            std::string arg = flag.substr(flag.find('=') + 1);

            try {
                size_t pos{};
                timeout = std::stoi(arg, &pos);
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        } else if (flag == "--json") {
            if (i != argc - 1) {
                jsonFile = argv[++i];
            } else {
                std::cerr << "Missing json file path after --json flag" << std::endl;
                return EXIT_FAILURE;
            }
        } else if (flag == "--junit") {
            if (i != argc - 1) {
                jUnitFile = argv[++i];
            } else {
                std::cerr << "Missing jUnit file path after --junit flag" << std::endl;
            }
        } else {
            renderUsage(argv[i]);
            return EXIT_FAILURE;
        }
    }

    internal::Core::TestRun& testRun = internal::Runner::getTestRun();

    internal::Runner::runAllRegisteredTests(testRun, num_threads, timeout, unit);

    internal::Renderer::ConsoleRenderer renderer(jsonFile, jUnitFile, verbFlag);

    renderer.render(testRun);
    return EXIT_SUCCESS;
}
