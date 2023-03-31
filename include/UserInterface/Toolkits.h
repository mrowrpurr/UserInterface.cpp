#pragma once

// #include <Logging.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "IToolkit.h"
#include "Private/Util.h"

namespace UserInterface {

    class Toolkits {
        std::unordered_map<std::string, std::shared_ptr<IToolkit>> _toolkits;

        std::string NormalizeName(const char* name) { return Private::Util::ToLower(name); }

    public:
        bool RegisterToolkit(const char* name, void* toolkit) {
            auto registeredName = NormalizeName(name);
            if (_toolkits.find(registeredName) != _toolkits.end()) {
                // Log("Toolkit '{}' already registered", name);
                return false;
            }
            _toolkits[registeredName] =
                std::shared_ptr<IToolkit>(reinterpret_cast<IToolkit*>(toolkit));
            return true;
        }

        template <typename T>
        bool RegisterToolkit(const char* name) {
            return RegisterToolkit(name, new T());
        }

        bool UnregisterToolkit(const char* name) {
            auto registeredName = NormalizeName(name);
            if (_toolkits.find(registeredName) == _toolkits.end()) {
                // Log("Toolkit '{}' not registered", name);
                return false;
            }
            _toolkits.erase(registeredName);
            return true;
        }

        IToolkit* GetToolkit(const char* name) {
            auto registeredName = NormalizeName(name);
            if (_toolkits.find(registeredName) == _toolkits.end()) {
                // Log("Toolkit '{}' not registered", name);
                return nullptr;
            }
            return _toolkits[registeredName].get();
        }

        bool IsToolkitRegistered(const char* name) {
            auto registeredName = NormalizeName(name);
            return _toolkits.find(registeredName) != _toolkits.end();
        }
    };
}
