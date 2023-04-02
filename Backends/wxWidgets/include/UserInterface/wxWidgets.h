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
            std::shared_ptr<wxWindowImpl> _mainWindow;

        public:
            wxApplicationImpl() : _mainWindow(new wxWindowImpl("")) {}

            virtual bool OnInit() {
                _mainWindow->Show(true);
                return true;
            }

            std::shared_ptr<wxWindowImpl> GetMainWindow() { return _mainWindow; }
        };
    }

    class Tab : public UITab {
        std::string _id;
        std::string _name;

    public:
        Tab(const char* id) : _id(id) {}
        const char* GetTitle() override { return _name.c_str(); }
        void        SetTitle(const char* title) override { _name = title; }
    };

    class Window : public UIWindow {
        std::string                         _id;
        std::shared_ptr<Impl::wxWindowImpl> _impl;

    public:
        Window(const char* id) : _id(id), _impl(std::make_unique<Impl::wxWindowImpl>(id)) {}

        Window(const char* id, std::shared_ptr<Impl::wxWindowImpl> impl) : _id(id), _impl(impl) {}

        const char* GetId() override { return _id.c_str(); }

        bool Show() override {
            _impl->Show(true);
            return true;
        }

        bool SetTitle(const char* title) override {
            _impl->SetTitle(title);
            return true;
        }

        UIWidget* AddWidget(const char* widgetType, const char* widgetId) override {
            return nullptr;
        }

        UITab* NewTab(const char* tabId, const char* tabName) override { return nullptr; }
    };

    class Application : public UIApplication {
        // wxWidgets is responsible for the destruction of the wxApp instance
        Impl::wxApplicationImpl* _impl;

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
                _windows.emplace(
                    windowId, std::make_unique<Window>(windowId, _impl->GetMainWindow())
                );
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
