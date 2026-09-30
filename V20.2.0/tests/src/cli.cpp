#include <testpp/testpp.hpp>
#include "../../cli/headers/Configure.hpp"
#include "../../cli/headers/Metadata.hpp"

#include <iostream>
#include <fstream>

D_TEST(configure) {
    testppCLI::Config conf;
    std::cout << conf << std::endl;

    conf.Serialize("DEFAULT_CONFIG_SERIALIZATION.conf");

    testppCLI::Config deserialized = testppCLI::Config::Deserialize("DEFAULT_CONFIG_SERIALIZATION.conf");

    std::cout << conf << std::endl;
}

D_TEST(cxx) {
    testppCLI::CXX cxx;
    std::cout << cxx << std::endl;

    cxx.Serialize("DEFAULT_CXX_SERIALIZE.conf");

    testppCLI::CXX deserialized = testppCLI::CXX::Deserialize("DEFAULT_CXX_SERIALIZE.conf");

    std::cout << cxx << std::endl;
}

D_TEST(metadata) {
    testppCLI::Metadata meta;
    meta.Serialize("DEFAULT_METADATA.data");
}