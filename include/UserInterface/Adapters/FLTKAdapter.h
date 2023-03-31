#pragma once

#include <Logging.h>

#include "../IToolkit.h"

namespace UserInterface::Adapters {

    class FLTKAdapter : public IToolkit {
    public:
        void RunWindow(Window* window) override { Log("YAY THIS WILL RUN THE WINDOW!"); }
    };
}
