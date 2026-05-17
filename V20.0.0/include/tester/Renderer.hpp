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
                ConsoleRenderer(Core::Verbosity verbosity = Core::Verbosity::Default) : verb(verbosity) {};
                void render(Core::TestRun& result) override;

            private:
                Core::Verbosity verb;
                void renderAll(Core::TestRun& result);
                void renderMinimum(Core::TestRun& result);
                void renderVerbose(Core::TestRun& result);
                void renderDefault(Core::TestRun& result);
        };
        
    }
}

#endif