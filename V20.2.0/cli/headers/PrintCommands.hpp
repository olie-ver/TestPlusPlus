#pragma once

#ifndef TESTPP_PRINT_COMMANDS_H
#define TESTPP_PRINT_COMMANDS_H

#define VERSION "20.2.0"

#include <array>
#include <string_view>

namespace testppCLI {
    void help();

    void diagnostics();

    void version();

    void listExecs();

    void inspect(int argc, char** argv);

    void usage(std::string_view bad_flag);
}

#endif