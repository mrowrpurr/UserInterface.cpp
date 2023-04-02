#pragma once

#include <memory>
#include <vector>

#include "Application.h"
#include "Toolkits.h"
#include "Window.h"


namespace UserInterface {

    class UIManager {
        UIManager()                            = default;
        ~UIManager()                           = default;
        UIManager(const UIManager&)            = delete;
        UIManager(UIManager&&)                 = delete;
        UIManager& operator=(const UIManager&) = delete;
        UIManager& operator=(UIManager&&)      = delete;

        std::vector<std::shared_ptr<Application>> _applications;
        std::vector<std::shared_ptr<Window>>      _windows;
        Toolkits                                  _toolkits;

    public:
        static UIManager& GetInstance() {
            static UIManager uiManager;
            return uiManager;
        }

        Toolkits* GetToolkits() { return &_toolkits; }

        Application* NewApplication() {
            _applications.emplace_back(std::make_shared<Application>(&_toolkits));
            return _applications.back().get();
        }

        Window* NewWindow() {
            _windows.emplace_back(std::make_shared<Window>());
            return _windows.back().get();
        }
    };
}
