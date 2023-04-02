#pragma once

#include <functional>

namespace UserInterface::Private {

    class FunctionRunner {
        std::function<void()> _function;

    public:
        FunctionRunner(std::function<void()> function) : _function(function) { function(); }
    };
}
