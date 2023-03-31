#pragma once

#include "../Config.h"
#include "../Private/FunctionRunner.h"

#if __has_include(<nana/gui.hpp>)
    #include "NanaAdapter.h"
UserInterface::Private::FunctionRunner __nanaAdapterRegistration([]() {
    UserInterface::Config::SetAdapter<UserInterface::Adapters::NanaAdapter>();
});
#endif
