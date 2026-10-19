#include "../../headers/print_commands.hpp"

#include <iostream>

namespace testppCLI {
    void version() {
        std::cout << "Test++ Version " << VERSION << std::endl;
    }
}