// #include "../headers/Helpers.hpp"
// #include "../headers/CLI.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)
    #include <algorithm>
#endif

// namespace tppHelpers {
//     void getFilesAndArgs(int argc, char** argv,
//         std::vector<std::string>& args, 
//         std::vector<std::filesystem::path>& files
//     ) 
//     {
//         for (int i = 1; i < argc; i++) {
//             std::filesystem::path p(argv[i]);

//             if (std::filesystem::is_regular_file(p))
//             {
//                 files.push_back(std::filesystem::absolute(p));
//             } 
//             else if (std::filesystem::is_directory(p))
//             {
//                 for (const auto& entry :
//                     std::filesystem::recursive_directory_iterator(p))
//                 {
//                     if (entry.path().extension() == ".cpp" || entry.path().extension() == ".cc")
//                     {
//                         files.push_back(std::filesystem::absolute(entry.path()));
//                     }
//                 }
//             } else {
//                 args.push_back(p.string());
//             }
//         }
//     }

//     void generateCMake(
//         const std::filesystem::path& install_prefix,
//         const std::filesystem::path& write_loc,
//         const std::filesystem::path& cmake_template, 
//         const std::vector<std::filesystem::path>& files,
//         const tppCLI::CXX& cxxFlags
//     ) 
//     {
//         const std::string installReplace = "@INSTALL_PREFIX@";
//         const std::string replace = "@USER_SOURCES@";
//         const std::string cxxReplace = "@USER_CXX_FLAGS@";
//         const std::string stdReplace = "@CXX_STANDARD@";
//         const std::string libReplace = "@USER_LIBS@";

//         std::ifstream readCmakeTemplate(cmake_template);
//         std::stringstream cmake;
//         cmake << readCmakeTemplate.rdbuf();
//         std::string generate_executable(cmake.str());

//         std::ostringstream imploded;
//         for (size_t i = 0; i < files.size(); i++) {
//             imploded << files[i] << "\n\t";
//         }

//         std::string install_str = install_prefix.string();
//         std::string imploded_str = imploded.str();

//         imploded.clear();
//         size_t pos;
//         std::string libraries = cxxFlags.libraries;
//         std::string lib;
//         while ((pos = cxxFlags.libraries.find(',')) != std::string::npos) {
//             lib = libraries.substr(0, pos);
//             imploded << lib << '\n\t';
//             libraries.erase(0UL, pos + 1);
//         }
//         imploded << libraries;
//         std::string lib_str = imploded.str();

//         #if defined(_WIN32) || defined(_WIN64)
//             for(size_t i = 0; i < install_str.size(); i++) {
//                 if (install_str[i] == '\\') {
//                     install_str.insert(i, 1, '\\');
//                     i++;
//                 }
//             }
//         #endif

//         generate_executable.replace(
//             generate_executable.find(installReplace),
//             installReplace.size(),
//             install_str
//         );

//         generate_executable.replace(
//             generate_executable.find(replace),
//             replace.size(),
//             imploded_str
//         );

//         generate_executable.replace(
//             generate_executable.find(cxxReplace),
//             cxxReplace.size(),
//             cxxFlags.flags
//         );

//         generate_executable.replace(
//             generate_executable.find(stdReplace),
//             stdReplace.size(),
//             cxxFlags.standard
//         );

//         generate_executable.replace(
//             generate_executable.find(libReplace),
//             libReplace.size(),
//             lib_str
//         );

//         std::ofstream out(write_loc);
//         out << generate_executable;
//         out.close();
//     }

//     bool configureAndBuild(const std::filesystem::path& run) {    
//         std::string build_dir = run.string();

//         std::string configure = "cmake -S \"" + build_dir +  "\" -B \"" + build_dir + "\"";

//         int configResult = std::system(configure.c_str());

//         if (configResult != 0) {
//             std::cerr << "Failed to configure project" << std::endl;
//             return false;
//         }

//         #if defined(_WIN32) || defined(_WIN64)
//             std::string build = "cmake --build \"" + build_dir + "\" --config Release";
//         #else
//             std::string build = "cmake --build \"" + build_dir + "\"";
//         #endif

//         int buildResult = std::system(build.c_str());

//         if (buildResult != 0) {
//             std::cerr << "Failed to build project" << std::endl;
//             return false;
//         }

//         return true;
//     }
// }