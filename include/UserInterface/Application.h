#pragma once

#include "Config.h"
#include "IWindow.h"


namespace UserInterface {

    class Application {
    public:
        template <IWindow WindowType>
        static void Run() {}
    };
}
