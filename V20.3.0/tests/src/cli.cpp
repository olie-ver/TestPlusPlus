#include <testpp/testpp.hpp>
#include "../../cli/headers/Configure.hpp"
#include "../../cli/headers/Metadata.hpp"

#include <iostream>
#include <fstream>

D_TEST(configure) {
    testppCLI::Config conf;
    std::cout << conf << std::endl;

    conf.Serialize("default_flag.conf");

    testppCLI::Config deserialized = testppCLI::Config::Deserialize("default_flag.conf");

    std::cout << conf << std::endl;
}

D_TEST(cxx) {
    testppCLI::CXX cxx;
    std::cout << cxx << std::endl;

    cxx.Serialize("default_cxx.conf");
    cxx.include = "/Users/oliverlie/Documents/GitHub/TestPlusPlus/test.cmake";
    cxx.Serialize("Changed_cxx.conf");

    testppCLI::CXX deserialized = testppCLI::CXX::Deserialize("Changed_cxx.conf");

    std::cout << cxx << std::endl;
    std::cout << deserialized << std::endl;
}

D_TEST(metadata) {
    testppCLI::Metadata meta;
    meta.Serialize("default_meta.data");

    testppCLI::Metadata deserialized = testppCLI::Metadata::Deserialize("default_meta.data");
    ASSERT_EQ(meta, deserialized);

    // deserialized.files = "tests/src/assert.cpp";
    // deserialized.Serialize("CHANGED_METADATA.data");

    // testppCLI::Metadata changed = testppCLI::Metadata::Deserialize("CHANGED_METADATA.data");
    // ASSERT_EQ(deserialized, changed);
}