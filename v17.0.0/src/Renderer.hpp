#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "TestCore.hpp"

using namespace TestCore; 

namespace TestResultRenderer {
    class ITestRenderer {
        public:
            virtual ~ITestRenderer() = default;
            virtual void render(TestRunResult& result) = 0;
    };

    class ConsoleRenderer : public ITestRenderer {
        public:
            void render(TestRunResult& result) override;
    };
}

#endif