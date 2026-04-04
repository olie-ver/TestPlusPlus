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
                void render(Core::TestRun& result) override;
        };
        
    }
}

#endif