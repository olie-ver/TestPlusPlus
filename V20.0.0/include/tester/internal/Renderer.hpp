#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Core.hpp"

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A rendering namespace to render the output from running tests
    namespace Renderer {
        class ITestRenderer {
            public:
                virtual ~ITestRenderer() = default;
                virtual void render(Core::TestRun& result) = 0;
        };

        class ConsoleRenderer : public ITestRenderer {
            public:
                ConsoleRenderer(const std::string jsonFile = "", const std::string junitFile = "", 
                    Core::Verbosity verbosity = Core::Verbosity::Default) 
                    : jsonFile(jsonFile), junitFile(junitFile), verb(verbosity) {};

                void render(Core::TestRun& result) override;

            private:
                Core::Verbosity verb;
                const std::string jsonFile;
                const std::string junitFile;
                
                void renderDefaultJson(Core::TestRun& result);
                void renderMinimumJson(Core::TestRun& result);
                void renderPassOnlyJson(Core::TestRun& result);
                void renderFailAllJson(Core::TestRun& result);
                void renderFailMinJson(Core::TestRun& result);

                void renderDefaultXml(Core::TestRun& result);
                void renderMinimumXml(Core::TestRun& result);
                void renderPassOnlyXml(Core::TestRun& result);
                void renderFailAllXml(Core::TestRun& result);
                void renderFailMinXml(Core::TestRun& result);

                void renderDefault(Core::TestRun& result);
                void renderMinimum(Core::TestRun& result);
                void renderPassOnly(Core::TestRun& result);
                void renderFailAll(Core::TestRun& result);
                void renderFailMin(Core::TestRun& result);
        };
        
    }
}

#endif