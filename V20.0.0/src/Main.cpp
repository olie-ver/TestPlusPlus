#include <tester/internal/Core.hpp>
#include <tester/internal/Renderer.hpp>
#include <tester/internal/Runner.hpp>
#include <iostream>
#include <thread>
#include <unordered_set>
#include <string>
#include <sstream>

//Gets the verbosity flag from an argument
internal::Core::Verbosity getVerbFlag(const std::string& arg);

//Gets the number of threads from an argument
int getNumThreads(const std::string& arg);

//Gets the SUITES to skip testing for
void getSkip(const std::string& arg, std::unordered_set<std::string>& suites);

//Gets the SUITES to ONLY test
void getTestOnly(const std::string& arg, std::unordered_set<std::string>& suites);

int main(int argc, char** argv) {
    internal::Core::Verbosity verbFlag = internal::Core::Verbosity::Default;
    int num_threads = 1;
    std::unordered_set<std::string>& skipSuites = internal::Runner::getSkipSuites();
    std::unordered_set<std::string>& testOnlySuites = internal::Runner::getTestOnly();

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

                // std::cout << "NUM THREADS CREATED IS " << num_threads << std::endl;
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
        }
    }

    internal::Core::TestRun& testRun = internal::Runner::getTestRun();

    internal::Runner::runAllRegisteredTests(testRun, num_threads);

    internal::Renderer::ConsoleRenderer renderer(verbFlag);

    renderer.render(testRun);
    return EXIT_SUCCESS;
}

internal::Core::Verbosity getVerbFlag(const std::string &arg)
{
    if (arg == "minimum") {
        return internal::Core::Verbosity::Minimum;
    } else if (arg == "passonly" || arg == "pass_only") {
        return internal::Core::Verbosity::PassOnly;
    } else if (arg == "failonly" || arg == "fail_only"
        || arg == "failonlyall" || arg == "fail_only_all") 
    {
        return internal::Core::Verbosity::FailOnlyAll;
    } else if (arg == "failonlymin" || arg == "fail_only_min")
    {
        return internal::Core::Verbosity::FailOnlyMin;
    }

    return internal::Core::Verbosity::Default;
}

int getNumThreads(const std::string &arg)
{
    size_t pos{};
    //find out the max number of threads this hardware can support
    int max_threads = std::max(std::thread::hardware_concurrency(), 1u);

    //clamp the number of threads in the argument between 1 and the max
    return std::max(std::min(std::stoi(arg, &pos), max_threads), 1);
}

void getSkip(const std::string& arg, std::unordered_set<std::string>& suites)
{
    std::string suite;
    std::stringstream args(arg);

    while(std::getline(args, suite, ','))
    {
        // std::cout << "SKIPPING " + suite << std::endl;
        suites.insert(suite);
    }
}

void getTestOnly(const std::string &arg, std::unordered_set<std::string>& suites)
{
    std::string suite;
    std::stringstream args(arg);

    while(std::getline(args, suite, ','))
    {
        suites.insert(suite);
    }
}
