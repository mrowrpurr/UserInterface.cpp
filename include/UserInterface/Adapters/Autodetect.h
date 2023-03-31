#pragma once

#include "../Private/FunctionRunner.h"
#include "../UIManager.h"

#if __has_include(<FL/Fl.H>)
    #include "FLTKAdapter.h"
UserInterface::Private::FunctionRunner __fltkAdapterRegistration([]() {
    auto manager = UserInterface::UIManager::GetInstance()
                       .GetToolkits()
                       ->RegisterToolkit<UserInterface::Adapters::FLTKAdapter>("fltk");
});
#endif
