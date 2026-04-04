#include "Core.hpp"
#include "Renderer.hpp"
#include "Runner.hpp"

int main() {
    internal::Core::TestRun mockRun;

    internal::Runner::runAllRegisteredTests(mockRun);

    internal::Renderer::ConsoleRenderer renderer;

    renderer.render(mockRun);
    return EXIT_SUCCESS;
}