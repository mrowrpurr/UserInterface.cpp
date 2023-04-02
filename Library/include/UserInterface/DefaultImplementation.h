#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>

#include "Interfaces.h"

namespace UserInterface::Impl {

    class ToolkitRegistryImpl : public UIToolkitRegistry {
        std::unordered_map<std::string, std::unique_ptr<UIToolkit>> _toolkits;
        std::string                                                 _defaultToolkitName;

        // Converts std::string to lowercase
        std::string NormalizeName(const std::string& str) {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }

    public:
        bool IsToolkitAvailable(const char* toolkitName) override {
            auto registryName = NormalizeName(toolkitName);
            return _toolkits.find(registryName) != _toolkits.end();
        }

        UIToolkit* GetToolkit(const char* toolkitName) override {
            auto registryName = NormalizeName(toolkitName);
            auto it           = _toolkits.find(registryName);
            if (it == _toolkits.end()) return nullptr;
            return it->second.get();
        }

        bool RegisterToolkit(const char* toolkitName, UIToolkit* toolkit) override {
            auto registryName = NormalizeName(toolkitName);
            if (IsToolkitAvailable(toolkitName)) return false;
            _toolkits[registryName] = std::unique_ptr<UIToolkit>(toolkit);
            return true;
        }

        const char* GetDefaultToolkitName() override { return _defaultToolkitName.c_str(); }

        bool SetDefaultToolkitName(const char* toolkitName) override {
            auto registryName = NormalizeName(toolkitName);
            if (!IsToolkitAvailable(toolkitName)) return false;
            _defaultToolkitName = registryName;
            return true;
        }
    };

    class APIImpl : public UIAPI {
        ToolkitRegistryImpl _toolkitRegistry;

    public:
        UIApplication* GetApplication(const char* toolkitName) override {
            UIToolkit* toolkit = _toolkitRegistry.GetToolkit(toolkitName);
            if (!toolkit) return nullptr;
            return toolkit->GetApplication();
        }

        UIToolkitRegistry* GetToolkitRegistry() override { return &_toolkitRegistry; }
    };
}
