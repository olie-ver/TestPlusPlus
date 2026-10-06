#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"
#include "../../headers/Helpers.hpp"

#include <filesystem>
#include <iostream>
#include <string_view>

namespace testppCLI {
    void configureFlags(int argc, char** argv) {
        const std::filesystem::path& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        Config config = Config::Deserialize(lastExecDir / "flags.conf");

        std::cout << "Config before: " << config << '\n';
        
        configConf(config, argc, argv);

        std::cout << "Config after: " << config << '\n';

        config.Serialize(lastExecDir / "flags.conf");
    }

    void configureCXX(int argc, char** argv) {
        const std::filesystem::path& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        CXX cxx = CXX::Deserialize(lastExecDir / "cxx.conf");

        std::cout << "cxx before: " << cxx << '\n';

        configCxx(cxx, argc, argv);

        std::cout << "cxx after: " << cxx << '\n';

        cxx.Serialize(lastExecDir / "cxx.conf");

        Metadata meta = Metadata::Deserialize(lastExecDir / "meta.data");
        meta.compile = true;
        meta.Serialize(lastExecDir / "meta.data");
    }

    void configureLink(int argc, char** argv) {
        const std::filesystem::path& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        CXX cxx = CXX::Deserialize(lastExecDir / "cxx.conf");

        std::cout << "cxx before: " << cxx << '\n';

        configLibs(cxx, argc, argv);

        std::cout << "cxx after: " << cxx << '\n';

        cxx.Serialize(lastExecDir / "cxx.conf");

        Metadata meta = Metadata::Deserialize(lastExecDir / "meta.data");
        meta.compile = true;
        meta.Serialize(lastExecDir / "meta.data");
    }

    void configureInclude(int argc, char** argv) {
        const std::filesystem::path& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        CXX cxx = CXX::Deserialize(lastExecDir / "cxx.conf");

        std::cout << "cxx before: " << cxx << '\n';

        configInclude(cxx, argc, argv);

        std::cout << "cxx after: " << cxx << '\n';

        cxx.Serialize(lastExecDir / "cxx.conf");

        Metadata meta = Metadata::Deserialize(lastExecDir / "meta.data");
        meta.compile = true;
        meta.Serialize(lastExecDir / "meta.data");
    }
}