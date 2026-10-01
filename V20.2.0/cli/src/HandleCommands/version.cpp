#include "../../headers/PrintCommands.hpp"

#include <iostream>

namespace testppCLI {
    void version() {
        std::cout << "Test++ Version " << VERSION << std::endl;
    }
}