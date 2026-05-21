#include <tester/internal/Core.hpp>
#include <tester/internal/Renderer.hpp>
#include <tester/internal/Runner.hpp>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
    internal::Core::Verbosity verbFlag;
    int num_threads = 1;

    // process the arguments
    for (int i = 1; i < argc; i++) {
        std::string flag(argv[i]);
        std::transform(flag.begin(), flag.end(), flag.begin(), 
            [](unsigned char c) { return std::tolower(c); });

        if (flag.find("--v=") != std::string::npos 
            || flag.find("--verbosity=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);
            if (arg == "default") {
                verbFlag = internal::Core::Verbosity::Default;
                std::cout << "Verbosity flag is DEFAULT" << std::endl;
            } else {
                verbFlag = internal::Core::Verbosity::Minimum;
                std::cout << "Verbosity flag is MINIMUM" << std::endl;
            }
        } else if (flag.find("--num_threads=") != std::string::npos
            || flag.find("--threads=") != std::string::npos
            || flag.find("--t=") != std::string::npos)
        {
            std::string arg = flag.substr(flag.find('=') + 1);
            size_t pos{};

            try {
                //find out the max number of threads this hardware can support
                int max_threads = std::thread::hardware_concurrency();

                //clamp the number of threads in the argument between 1 and the max
                num_threads = std::max(std::min(std::stoi(arg, &pos), max_threads), 1);

                std::cout << "NUM THREADS CREATED IS " << num_threads << std::endl;
            } catch (std::invalid_argument const& ex) {
                std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            } catch (std::out_of_range const& ex) {
                std::cerr << "std::out_of_range::what(): " << ex.what() << '\n';
                return EXIT_FAILURE;
            }
        }
    }

    internal::Core::TestRun& testRun = internal::Runner::makeTestRun();

    internal::Runner::runAllRegisteredTests(testRun, num_threads);

    internal::Renderer::ConsoleRenderer renderer(verbFlag);

    renderer.render(testRun);
    return EXIT_SUCCESS;
}