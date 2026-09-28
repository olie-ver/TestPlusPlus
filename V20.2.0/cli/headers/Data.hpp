#pragma once

#ifndef TESTPP_CLI_DATA_H
#define TESTPP_CLI_DATA_H

#include <array>
#include <string_view>

namespace tppCLI {
    static constinit const std::array<std::string_view, 2> verbArgs{
        "--v=", "--verbosity="
    };

    static constinit const std::array<std::string_view, 3> threadArgs{
        "--t=", "--threads=", "--numthreads="
    };

    static constinit const std::array<std::string_view, 2> skipArgs{
        "--s=", "--skip="
    };

    static constinit const std::array<std::string_view, 4> testArgs{
        "--testonly=", "--test_only=", "--to=", "--t_o="
    };

    static constinit const std::array<std::string_view, 3> timeArgs{
        "--timeout=", "--timeout_sec=", "--timeout_ms="
    };

    static constinit const std::array<std::string_view, 9> validFlags{
        "--json", //JSON
        "--junit", "--xml", //XML
        "--stdout=", "--stdoutsize=", //stdout length (isolation)
        "--stderr=", "--stderrsize=", //stderr length (isolation)
        "--truncate", //stdout/stderr length truncation (1024 chars) (isolation)
        "--stream" //streaming
    };

    static constinit const std::array<std::string_view, 10> validArgs{
        "minimum", "passonly", "pass_only", "failonly", "fail_only", "failonlyall", "fail_only_all", 
        "failonlymin", "fail_only_min", "default", //verbosity
    };
}

#endif