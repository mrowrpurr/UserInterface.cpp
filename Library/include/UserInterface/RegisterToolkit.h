#pragma once

#include <functional>

namespace UserInterface::ToolkitRegistration::Private {
    class FunctionRunner {
        std::function<void()> _function;

    public:
        FunctionRunner(std::function<void()> function) : _function(function) { function(); }
    };
}

#define UserInterface_RegisterToolkit(name, toolkitClassName)               \
    UserInterface::ToolkitRegistration::Private::FunctionRunner             \
        __RegisterUserInterfaceTookkit_##name([]() {                        \
            UserInterface::GetAPI()->GetToolkitRegistry()->RegisterToolkit( \
                #name, new toolkitClassName()                               \
            );                                                              \
        });
