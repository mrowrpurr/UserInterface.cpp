#pragma once

#include "../Private/FunctionRunner.h"
#include "../UIManager.h"

#if __has_include(<FL/Fl.H>)
    #include "FLTKAdapter.h"
UserInterface::Private::FunctionRunner __fltkAdapterRegistration([]() {
    UserInterface::UIManager::GetInstance()
        .GetToolkits()
        ->RegisterToolkit<UserInterface::Adapters::FLTKAdapter>("FLTK");
});
#endif

#if __has_include(<nana/gui.hpp>)
    #include "NanaAdapter.h"
UserInterface::Private::FunctionRunner __nanaAdapterRegistration([]() {
    UserInterface::UIManager::GetInstance()
        .GetToolkits()
        ->RegisterToolkit<UserInterface::Adapters::NanaAdapter>("Nana");
});
#endif

#if __has_include(<wx/wx.h>)
    #include "wxWidgetsAdapter.h"
UserInterface::Private::FunctionRunner __wxWidgetsAdapterRegistration([]() {
    UserInterface::UIManager::GetInstance()
        .GetToolkits()
        ->RegisterToolkit<UserInterface::Adapters::wxWidgetsAdapter>("wxWidgets");
});
#endif
