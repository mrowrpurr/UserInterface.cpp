#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <UserInterface/Interfaces.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace UserInterface::FLTK {

    namespace Impl {}

    class Window : public UIWindow {
        std::string _id;
        Fl_Window*  _impl;

    public:
        Window(const char* id) : _id(id) {
            _impl = new Fl_Window(500, 300, "FLTK Sample");
            _impl->begin();
            // ...
            _impl->end();
            _impl->show();
        }

        const char* GetId() override { return _id.c_str(); }

        UIApplication* GetApplication() override { return nullptr; }

        bool Show() override {
            // _impl->Show(true);
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
        void Run() override { Fl::run(); }

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
