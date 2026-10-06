#include "../../headers/Metadata.hpp"

#include "../../headers/FileSystem.hpp"

#ifdef __APPLE__
    #include <mach-o/dyld.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

#include <fstream>

namespace testppCLI {
    std::filesystem::path GetInstallRoot() {
        #ifdef __APPLE__
            uint32_t size = 0;
            _NSGetExecutablePath(nullptr, &size);

            std::string buffer(size, '\0');
            _NSGetExecutablePath(buffer.data(), &size);

            auto exePath = std::filesystem::canonical(std::filesystem::path(buffer.c_str()));

            return exePath.parent_path().parent_path();
        #elif defined(__linux__)
            std::filesystem::path exe = std::filesystem::canonical("/proc/self/exe");
            return exe.parent_path().parent_path();
        #elif defined(_WIN32) || defined(_WIN64)
            wchar_t buffer[MAX_PATH];
            GetModuleFileNameW(NULL, buffer, MAX_PATH);
            std::filesystem::path exePath(buffer);
            return exePath.parent_path().parent_path();
        #endif
    }

    std::filesystem::path GetLastExec() {
        std::filesystem::path filePath{GetInstallRoot() / "var" / "last_exec.conf"};
        std::ifstream reader{filePath};

        std::string line;
        std::getline(reader, line);
        std::filesystem::path lastExec{GetInstallRoot() / "run" / "testpp" / line};

        return lastExec;
    }

    Metadata GetMetadata(std::string_view name) {
        std::filesystem::path metadata{GetInstallRoot() / "run" / "testpp" / name / "meta.data"};
        return Metadata::Deserialize(metadata);
    }
}