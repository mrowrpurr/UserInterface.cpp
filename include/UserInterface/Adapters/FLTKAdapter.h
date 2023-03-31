#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
// #include <Logging.h>

#include "../IToolkit.h"

namespace UserInterface::Adapters {

    class FLTKAdapter : public IToolkit {
    public:
        void RunWindow(Window* window) override {
            Fl_Window win(500, 300, "FLTK Sample");
            win.show();
            Fl::run();
        }
    };
}
