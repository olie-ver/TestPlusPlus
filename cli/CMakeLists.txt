#The CLI contains the files needed to create a CLI executable

cmake_minimum_required(VERSION 3.20)

add_executable(testpp_cli
    src/Main.cpp

    src/Config/ConfigureSettings.cpp
    src/Config/GlobalConfigure.cpp
    src/Config/Metadata.cpp
    src/Config/Serialize.cpp
    src/Config/Stream.cpp

    src/Filesystem/Exec.cpp
    src/FileSystem/FileSystem.cpp

    src/HandleCommands/diagnostics.cpp
    src/HandleCommands/help.cpp
    src/HandleCommands/inspect.cpp
    src/HandleCommands/listExecs.cpp
    src/HandleCommands/usage.cpp
    src/HandleCommands/version.cpp

    src/Helpers/buildCMake.cpp
    src/Helpers/buildExec.cpp
    src/Helpers/configConf.cpp
    src/Helpers/getFilesAndArgs.cpp
    src/Helpers/rename.cpp
    src/Helpers/replace.cpp
    src/Helpers/split.cpp

    src/ResetCommands/Default.cpp
    src/ResetCommands/GlobalDefault.cpp
    src/ResetCommands/GlobalReset.cpp
    src/ResetCommands/Reset.cpp
)

target_compile_features(testpp_cli PRIVATE cxx_std_20)

set_target_properties(testpp_cli PROPERTIES
    OUTPUT_NAME testpp
)