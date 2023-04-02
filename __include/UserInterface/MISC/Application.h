#pragma once

// #include <Logging.h>

#include "Toolkits.h"
#include "Window.h"

namespace UserInterface {

    class Application {
        Toolkits* _toolkits;

    public:
        Application(Toolkits* toolkits) : _toolkits(toolkits) {}

        void RunWindow(Window* window, const char* toolkitName) {
            auto* toolkit = _toolkits->GetToolkit(toolkitName);
            if (toolkit) toolkit->RunWindow(window);
            // else Log("No toolkit named '{}' found", toolkitName);
        }
    };
}
