#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Interfaces.h"

namespace UserInterface::Impl {

    class ToolkitRegistryImpl : public UIToolkitRegistry {
        std::unordered_map<std::string, std::unique_ptr<UIToolkit>> _toolkits;
        std::string                                                 _defaultToolkitName;

    public:
        bool IsToolkitAvailable(const char* toolkitName) override {
            return _toolkits.find(toolkitName) != _toolkits.end();
        }

        UIToolkit* GetToolkit(const char* toolkitName) override {
            auto it = _toolkits.find(toolkitName);
            if (it == _toolkits.end()) return nullptr;
            return it->second.get();
        }

        bool RegisterToolkit(const char* toolkitName, UIToolkit* toolkit) override {
            if (IsToolkitAvailable(toolkitName)) return false;
            _toolkits[toolkitName] = std::unique_ptr<UIToolkit>(toolkit);
            return true;
        }

        const char* GetDefaultToolkitName() override { return _defaultToolkitName.c_str(); }

        bool SetDefaultToolkitName(const char* toolkitName) override {
            if (!IsToolkitAvailable(toolkitName)) return false;
            _defaultToolkitName = toolkitName;
            return true;
        }
    };

    class APIImpl : public UIAPI {
        ToolkitRegistryImpl _toolkitRegistry;

    public:
        UIApplication* NewApplication(const char* toolkitName) override {
            UIToolkit* toolkit = _toolkitRegistry.GetToolkit(toolkitName);
            if (!toolkit) return nullptr;
            return toolkit->NewApplication();
        }

        UIToolkitRegistry* GetToolkitRegistry() override { return &_toolkitRegistry; }
    };
}
