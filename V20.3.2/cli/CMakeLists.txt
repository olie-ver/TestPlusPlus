#The CLI contains the files needed to create a CLI executable

cmake_minimum_required(VERSION 3.20)

add_executable(testpp_cli
    src/main.cpp

    src/config/configure_settings.cpp
    src/config/global_configure.cpp
    src/config/metadata.cpp
    src/config/serialize.cpp
    src/config/stream.cpp

    src/file_system/exec.cpp
    src/file_system/file_system.cpp

    src/handle_commands/diagnostics.cpp
    src/handle_commands/help.cpp
    src/handle_commands/inspect.cpp
    src/handle_commands/list_execs.cpp
    src/handle_commands/usage.cpp
    src/handle_commands/version.cpp

    src/helpers/build_cmake.cpp
    src/helpers/build_exec.cpp
    src/helpers/config_conf.cpp
    src/helpers/get_files_and_args.cpp
    src/helpers/rename.cpp
    src/helpers/replace.cpp
    src/helpers/split.cpp

    src/reset_commands/default.cpp
    src/reset_commands/global_default.cpp
    src/reset_commands/global_reset.cpp
    src/reset_commands/reset.cpp
)

target_compile_features(testpp_cli PRIVATE cxx_std_20)

set_target_properties(testpp_cli PROPERTIES
    OUTPUT_NAME testpp
)