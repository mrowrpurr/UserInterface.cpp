#pragma once

// #include <Logging.h>

#include <nana/gui.hpp>

#include "../IToolkit.h"

namespace UserInterface::Adapters {

    class NanaAdapter : public IToolkit {
    public:
        void RunWindow(Window* window) override {
            nana::form fm{nana::API::make_center(500, 300)};
            fm.caption("Nana GUI Sample");
            fm.show();
            nana::exec();
        }
    };
}
