#include "../../headers/Configure.hpp"

#include <fstream>

namespace testppCLI {
    void Config::Serialize(const std::filesystem::path& path) {
        std::ofstream file(path, std::ios::binary | std::ios::trunc);

        file.write(reinterpret_cast<char*>(&num_threads), sizeof(num_threads));
        file.write(reinterpret_cast<char*>(&timeout), sizeof(timeout));
        file.write(reinterpret_cast<char*>(&stdoutSize), sizeof(stdoutSize));
        file.write(reinterpret_cast<char*>(&stderrSize), sizeof(stderrSize));
        file.write(reinterpret_cast<char*>(&stream), sizeof(stream));
        file.write(reinterpret_cast<char*>(&timeUnit), sizeof(timeUnit));

        uint64_t jsonFileSize = jsonFile.length();
        file.write(reinterpret_cast<char*>(&jsonFileSize), sizeof(jsonFileSize));
        file.write(jsonFile.data(), jsonFileSize);

        uint64_t junitFileSize = jUnitFile.length();
        file.write(reinterpret_cast<char*>(&junitFileSize), sizeof(junitFileSize));
        file.write(jUnitFile.data(), junitFileSize);

        uint64_t verbositySize = verbosity.length();
        file.write(reinterpret_cast<char*>(&verbositySize), sizeof(verbositySize));
        file.write(verbosity.data(), verbositySize);

        uint64_t skipSize = skipSuites.length();
        file.write(reinterpret_cast<char*>(&skipSize), sizeof(skipSize));
        file.write(skipSuites.data(), skipSize);

        uint64_t testSize = testOnlySuites.length();
        file.write(reinterpret_cast<char*>(&testSize), sizeof(testSize));
        file.write(testOnlySuites.data(), testSize);
    }

    Config Config::Deserialize(const std::filesystem::path& path) {
        Config conf;
        std::ifstream file(path, std::ios::binary);

        file.read(reinterpret_cast<char*>(&conf.num_threads), sizeof(conf.num_threads));
        file.read(reinterpret_cast<char*>(&conf.timeout), sizeof(conf.timeout));
        file.read(reinterpret_cast<char*>(&conf.stdoutSize), sizeof(conf.stdoutSize));
        file.read(reinterpret_cast<char*>(&conf.stderrSize), sizeof(conf.stderrSize));
        file.read(reinterpret_cast<char*>(&conf.stream), sizeof(conf.stream));
        file.read(reinterpret_cast<char*>(&conf.timeUnit), sizeof(conf.timeUnit));

        uint64_t jsonFileSize;
        file.read(reinterpret_cast<char*>(&jsonFileSize), sizeof(jsonFileSize));
        conf.jsonFile.resize(jsonFileSize);
        file.read(conf.jsonFile.data(), jsonFileSize);

        uint64_t junitFileSize;
        file.read(reinterpret_cast<char*>(&junitFileSize), sizeof(junitFileSize));
        conf.jUnitFile.resize(junitFileSize);
        file.read(conf.jUnitFile.data(), junitFileSize);

        uint64_t verbositySize;
        file.read(reinterpret_cast<char*>(&verbositySize), sizeof(verbositySize));
        conf.verbosity.resize(verbositySize);
        file.read(conf.verbosity.data(), verbositySize);

        uint64_t skipSize;
        file.read(reinterpret_cast<char*>(&skipSize), sizeof(skipSize));
        conf.skipSuites.resize(skipSize);
        file.read(conf.skipSuites.data(), skipSize);

        uint64_t testSize;
        file.read(reinterpret_cast<char*>(&testSize), sizeof(testSize));
        conf.testOnlySuites.resize(testSize);
        file.read(conf.testOnlySuites.data(), testSize);

        return conf;
    }

    void CXX::Serialize(const std::filesystem::path& path) {
        //open the file and clear all content
        std::ofstream file(path, std::ios::binary | std::ios::trunc);

        file.write(reinterpret_cast<char*>(&standard), sizeof(standard));

        uint64_t flagSize = flags.length();
        file.write(reinterpret_cast<char*>(&flagSize), sizeof(flagSize));
        file.write(flags.data(), flagSize);

        uint64_t libSize = linkLibs.length();
        file.write(reinterpret_cast<char*>(&libSize), sizeof(libSize));
        file.write(linkLibs.data(), libSize);
    }

    CXX CXX::Deserialize(const std::filesystem::path& path) {
        CXX cxx;
        std::ifstream file(path, std::ios::binary);

        file.read(reinterpret_cast<char*>(&cxx.standard), sizeof(cxx.standard));

        uint64_t flagSize;
        file.read(reinterpret_cast<char*>(&flagSize), sizeof(flagSize));
        cxx.flags.resize(flagSize);
        file.read(cxx.flags.data(), flagSize);

        uint64_t libSize;
        file.read(reinterpret_cast<char*>(&libSize), sizeof(libSize));
        cxx.linkLibs.resize(libSize);
        file.read(cxx.linkLibs.data(), libSize);

        return cxx;
    }
}