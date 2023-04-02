#pragma once

#include <UserInterface/Interfaces.h>

#include <QApplication>
#include <QWidget>
#include <memory>
#include <string>
#include <unordered_map>

namespace UserInterface::Qt {

    namespace Impl {}

    class Window : public UIWindow {
        std::string _id;
        QWidget     _impl;

    public:
        Window(const char* id) : _id(id) {
            _impl.setWindowTitle(id);
            _impl.show();
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
        std::unique_ptr<QApplication>                            _impl;
        std::unordered_map<std::string, std::unique_ptr<Window>> _windows;

    public:
        Application() {
            int    argc = 0;
            char** argv = nullptr;
            _impl       = std::make_unique<QApplication>(argc, argv);
        }

        void Run() override {
            int    argc = 0;
            char** argv = nullptr;
            _impl->exec();
        }

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
