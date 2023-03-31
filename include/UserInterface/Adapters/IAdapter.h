#pragma once

#include "../IWindow.h"

namespace UserInterface::Adapters {

    struct IAdapter {
        virtual void Run(IWindow& window) = 0;
    };
}
