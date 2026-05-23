cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(tester LANGUAGES CXX)

find_package(Threads REQUIRED)

add_library(tester
    src/Multithread.cpp
    src/ProcessArgs.cpp
    src/RenderConsole.cpp
    src/Renderer.cpp
    src/RenderJson.cpp
    src/RenderXml.cpp
    src/Runner.cpp
)

set_target_properties(tester PROPERTIES
    UNITY_BUILD ON
)

target_precompile_headers(tester PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tester/internal/PCH/pch.hpp"
)

target_compile_features(tester PUBLIC cxx_std_20)

target_include_directories(tester PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tester PUBLIC Threads::Threads)

if (MSVC)
    target_compile_options(tester PRIVATE /W4)
else()
    target_compile_options(tester PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Winvalid-pch
    )
endif()

add_executable(runTests
    src/Main.cpp
)

target_link_libraries(runTests PRIVATE tester)

enable_testing()

add_test(NAME framework_tests COMMAND runTests)