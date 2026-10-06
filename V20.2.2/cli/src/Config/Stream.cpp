#include "../../headers/Configure.hpp"
#include "../../headers/Helpers.hpp"

#include <iostream>

namespace testppCLI {
    std::ostream& operator<< (std::ostream& stream, const Config& config) {
        //verbosity
        stream << "--verbosity=" << config.verbosity << ' ';

        //num threads
        stream << "--numthreads=" << config.num_threads << ' ';

        //timeout
        if (config.timeUnit == Config::sec) {
            stream << "--timeout=";
        } else {
            stream << "--timeout_ms=";
        }
        stream << config.timeout << ' ';

        //jsonfile
        if (!config.jsonFile.empty()) {
            stream << "--json " << config.jsonFile << ' ';
        }

        //xml
        if (!config.jUnitFile.empty()) {
            stream << "--xml " << config.jUnitFile << ' ';
        }

        //skip
        if (!config.skipSuites.empty()) {
            stream << "--skip=" << config.skipSuites << ' ';
        }

        //test only
        if (!config.testOnlySuites.empty()) {
            stream << "--testonly=" << config.testOnlySuites << ' ';
        }

        //stdout truncation
        stream << "--stdoutsize=" << config.stdoutSize << ' ';
        //stderr truncation
        stream << "--stderrsize=" << config.stderrSize << ' ';

        if (config.stream) {
            stream << "--stream";
        }

        return stream;
    }

    std::ostream& operator<< (std::ostream& stream, const CXX& cxx) {
        //C++ standard:
        stream << "--std=c++" << std::to_string(cxx.standard) << ' ';

        //Compiler flags
        stream << cxx.flags << ' ';

        //Link Libraries
        stream << cxx.linkLibs << ' ';

        stream << "Include paths:\n";
        std::vector<std::string> includePaths{split(cxx.include, " ")};
        for (size_t i = 0; i < includePaths.size(); i++) {
            stream << '\t' << includePaths[i] << '\n';
        } 

        return stream;
    }
}