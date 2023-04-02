#pragma once

#include <UserInterface/Interfaces.h>
#include <wx/wx.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace UserInterface::wxWidgets {

    namespace Impl {
        class wxWindowImpl : public wxFrame {
        public:
            wxWindowImpl(const wxString& title)
                : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200)) {}
        };

        class wxApplicationImpl : public wxApp {
            wxWindowImpl* _mainWindow;

        public:
            wxApplicationImpl() : _mainWindow(new wxWindowImpl("")) {}

            virtual bool OnInit() {
                _mainWindow->Show(true);
                return true;
            }

            wxWindowImpl* GetMainWindow() { return _mainWindow; }
        };
    }

    class Window : public UIWindow {
        std::string         _id;
        Impl::wxWindowImpl* _impl;

    public:
        Window(const char* id) : _id(id), _impl(new Impl::wxWindowImpl(id)) {}
        Window(const char* id, Impl::wxWindowImpl* impl) : _id(id), _impl(impl) {}

        const char* GetId() override { return _id.c_str(); }

        UIApplication* GetApplication() override { return nullptr; }

        bool Show() override {
            _impl->Show(true);
            return true;
        }

        bool SetTitle(const char* title) override {
            _impl->SetTitle(title);
            return true;
        }
    };

    class Application : public UIApplication {
        Impl::wxApplicationImpl*                                 _impl;
        std::unordered_map<std::string, std::unique_ptr<Window>> _windows;

    public:
        Application() : _impl(new Impl::wxApplicationImpl()) {}

        void Run() override {
            wxApp::SetInstance(_impl);

            int    argc = 0;
            char** argv = nullptr;
            wxEntryStart(argc, argv);

            if (!wxTheApp || !wxTheApp->CallOnInit()) return;
            wxTheApp->OnRun();
            wxTheApp->OnExit();
            wxEntryCleanup();
        }

        UIWindow* NewWindow(const char* windowId) override {
            if (_windows.empty())
                _windows.emplace(windowId, new Window(windowId, _impl->GetMainWindow()));
            else _windows.emplace(windowId, std::make_unique<Window>(windowId));
            return _windows.at(windowId).get();
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
