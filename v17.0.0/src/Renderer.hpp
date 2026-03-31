#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "TestCore.hpp"

using namespace TestCore; 

namespace TestResultRenderer {
    class ITestRenderer {
        public:
            virtual ~ITestRenderer() = default;
            virtual void render(const TestRunResult& result) = 0;
    };

    class ConsoleRenderer : public ITestRenderer {
        public:
            void render(const TestRunResult& result) override;
    };
}

#endif