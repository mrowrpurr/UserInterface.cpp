#pragma once

#include "IAdapter.h"

namespace UserInterface::Adapters {

    class NanaAdapter : public IAdapter {
    public:
        void Run(IWindow& window) override {}
    };
}
