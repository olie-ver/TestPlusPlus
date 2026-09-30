#pragma once

#ifndef TESTPP_CLI_HELPERS_H
#define TESTPP_CLI_HELPERS_H

#include "Configure.hpp"

#include <string>
#include <vector>

namespace testppCLI {
    std::vector<std::string> split(std::string s, const std::string& delimiter);
    std::string implode(const std::vector<std::filesystem::path>& strs, const std::string& glue);
    
    void configConf(Config& conf, int argc, char** argv);
    void configCxx(CXX& cxx, int argc, char** argv);
    void configLibs(CXX& cxx, int argc, char** argv);

    void rename(int argc, char** argv);

    void buildCMake(std::string_view path);
    void buildExec(std::string_view name);
    std::string replace(const std::string& s, const std::string& delimiter, const std::string& replace);

    void getFilesAndArgs(int start, int argc, char** argv, std::vector<std::filesystem::path>& files, std::vector<std::string>& args);
}

#endif