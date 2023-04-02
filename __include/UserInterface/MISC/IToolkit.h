#pragma once

#include "Window.h"

namespace UserInterface {

    struct IToolkit {
        virtual void RunWindow(Window* window) = 0;
    };
}
