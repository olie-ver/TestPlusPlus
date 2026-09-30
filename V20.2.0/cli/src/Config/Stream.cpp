#include "../../headers/Configure.hpp"
#include "../../headers/Helpers.hpp"

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
            stream << "json " << config.jsonFile << ' ';
        }

        //xml
        if (!config.jUnitFile.empty()) {
            stream << "xml " << config.jUnitFile << ' ';
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
        stream << "--std=c++" << cxx.standard << ' ';

        //Compiler flags
        stream << cxx.flags << ' ';

        //Link Libraries
        stream << cxx.linkLibs << ' ';

        return stream;
    }
}