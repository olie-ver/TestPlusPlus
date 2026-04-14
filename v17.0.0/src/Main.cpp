#include <tester/Core.hpp>
#include <tester/Renderer.hpp>
#include <tester/Runner.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./runtests --verbosity-flag \n";
        std::cerr << "\t Supported --verbosity-flags: --default, --minimum";
        return EXIT_FAILURE;
    } 

    std::string flag = argv[1];
    internal::Core::Verbosity verbFlag;
    if (flag == "--default") {
        verbFlag = internal::Core::Verbosity::Default;
    } else {
        verbFlag = internal::Core::Verbosity::Minimum;
    }

    internal::Core::TestRun testRun;

    internal::Runner::runAllRegisteredTests(testRun);

    internal::Renderer::ConsoleRenderer renderer(verbFlag);

    renderer.render(testRun);
    return EXIT_SUCCESS;
}