#pragma once

#include <UserInterface/Interfaces.h>

#include <memory>
#include <nana/gui.hpp>
#include <string>
#include <unordered_map>

namespace UserInterface::Nana {

    namespace Impl {}

    class Window : public UIWindow {
        std::string _id;
        nana::form  _impl;

    public:
        Window(const char* id) : _id(id) {
            _impl.caption(id);
            _impl.show();
        }

        const char* GetId() override { return _id.c_str(); }

        UIApplication* GetApplication() override { return nullptr; }

        bool Show() override {
            // _impl->show();
            return true;
        }

        bool SetTitle(const char* title) override {
            // _impl->SetTitle(title);
            return true;
        }
    };

    class Application : public UIApplication {
        std::unordered_map<std::string, std::unique_ptr<Window>> _windows;

    public:
        void Run() override { nana::exec(); }

        UIWindow* NewWindow(const char* windowId) override {
            auto window        = std::make_unique<Window>(windowId);
            auto result        = window.get();
            _windows[windowId] = std::move(window);
            return result;
        }
    };

    class Toolkit : public UIToolkit {
        std::unique_ptr<Application> _application;

    public:
        UIApplication* GetApplication() override {
            if (!_application) _application = std::make_unique<Application>();
            return _application.get();
        }
    };
}
