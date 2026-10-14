#include "../../headers/PrintCommands.hpp"

#include <iostream>

namespace testppCLI {
    void usage(std::string_view bad_flag) {
        std::cout << "Unknown flag: " << bad_flag << '\n';
        help();
    }
}