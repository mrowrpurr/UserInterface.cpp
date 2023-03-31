#pragma once

#include <memory>

#include "Adapters/IAdapter.h"

namespace UserInterface::Config {
    std::shared_ptr<Adapters::IAdapter> CurrentAdapter;

    template <typename AdapterType>
    void SetAdapter() {
        CurrentAdapter = std::make_shared<AdapterType>();
    }
}
