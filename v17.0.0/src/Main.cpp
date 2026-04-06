#include <tester/Core.hpp>
#include <tester/Renderer.hpp>
#include <tester/Runner.hpp>

int main() {
    internal::Core::TestRun testRun;

    internal::Runner::runAllRegisteredTests(testRun);

    internal::Renderer::ConsoleRenderer renderer;

    renderer.render(testRun);
    return EXIT_SUCCESS;
}