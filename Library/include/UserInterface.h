#pragma once

#include "UserInterface/DefaultImplementation.h"
#include "UserInterface/Interfaces.h"
#include "UserInterface/UI_Main.h"

namespace UserInterface {
    inline UIAPI* GetAPI() {
        static Impl::APIImpl api;
        return &api;
    }
}
