#pragma once

#include <UserInterface/Interfaces.h>
#include <wx/notebook.h>
#include <wx/wx.h>

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace UserInterface::wxWidgets {

    namespace Impl {
        class wxWindowImpl : public wxFrame {
            std::function<void()> _onCloseCallback;

        public:
            wxWindowImpl(const wxString& title, std::function<void()> onCloseCallback)
                : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200)),
                  _onCloseCallback(onCloseCallback) {
                Bind(wxEVT_CLOSE_WINDOW, &wxWindowImpl::OnClose, this);
            }

            void OnClose(wxCloseEvent& event) {
                event.Veto();
                _onCloseCallback();
            }
        };

        class wxApplicationImpl : public wxApp {
            std::function<void()> _onInitCallback;

        public:
            wxApplicationImpl(std::function<void()> onInitCallback)
                : _onInitCallback(onInitCallback) {}

            virtual bool OnInit() {
                _onInitCallback();
                return true;
            }
        };
    }

    class Label : public UILabel {
    public:
        void        SetText(const char* text) {}
        const char* GetText() { return nullptr; }
    };

    class Textbox : public UITextbox {
    public:
        void        SetText(const char* text) {}
        const char* GetText() { return nullptr; }
    };

    class Button : public UIButton {
    public:
        void SetText(const char* text) {}
    };

    class WidgetContainer : public UIWidgetContainer {
    public:
        UILabel*   AddLabel(const char* text) override { return nullptr; }
        UITextbox* AddTextbox(const char* text) override { return nullptr; }
        UIButton*  AddButton(const char* text, void (*callback)()) override { return nullptr; }
    };

    class Window;

    class Tab : public WidgetContainer, public UITab {
        std::string _title;

    public:
        const char* GetTitle() override { return _title.c_str(); }
        void        SetTitle(const char*) override {}
        UILabel*    AddLabel(const char* text) override { return nullptr; }
        UITextbox*  AddTextbox(const char* text) override { return nullptr; }
        UIButton*   AddButton(const char* text, void (*callback)()) override { return nullptr; }
    };

    namespace {
        std::atomic<unsigned int> _nextWindowId = 0;
    }

    class Window : public WidgetContainer, public UIWindow {
        unsigned int _id = _nextWindowId++;

        bool                               _appInitialized = false;
        std::vector<std::function<void()>> _onInitCallbacks;

        std::function<void()> _onCloseCallback;

        bool                                _tabsInitialized = false;
        std::vector<std::unique_ptr<Tab>>   _tabs;
        std::unique_ptr<Impl::wxWindowImpl> _wxWindow;

        void PerformOnInitOrNow(std::function<void()> callback) {
            if (_appInitialized) callback();
            else _onInitCallbacks.push_back(callback);
        }

    public:
        Window(const std::string& title, std::function<void()> onCloseCallback)
            : _wxWindow(std::make_unique<Impl::wxWindowImpl>(title, onCloseCallback)) {}

        unsigned int                         GetId() const { return _id; }
        std::unique_ptr<Impl::wxWindowImpl>& GetWxWindow() { return _wxWindow; }

        void OnInit() {
            _appInitialized = true;
            for (auto& callback : _onInitCallbacks) callback();
            _onInitCallbacks.clear();
        }

        bool Show() override {
            PerformOnInitOrNow([this]() { _wxWindow->Show(true); });
            return true;
        }

        bool SetTitle(const char* title) override {
            PerformOnInitOrNow([this, title]() { _wxWindow->SetTitle(title); });
            return true;
        }

        UITab* AddTab(const char* tabTitle) override { return nullptr; }

        UILabel*   AddLabel(const char* text) override { return nullptr; }
        UITextbox* AddTextbox(const char* text) override { return nullptr; }
        UIButton*  AddButton(const char* text, void (*callback)()) override { return nullptr; }
    };

    class Application : public UIApplication {
        std::unordered_map<unsigned int, std::unique_ptr<Window>> _windows;
        Impl::wxApplicationImpl*                                  _wxApplication;

    public:
        Application()
            : _wxApplication(new Impl::wxApplicationImpl([this]() {
                  for (auto& [id, window] : _windows) window->OnInit();
              })) {}

        void Run() override {
            wxApp::SetInstance(_wxApplication);

            int    argc = 0;
            char** argv = nullptr;
            if (wxEntryStart(argc, argv)) {
                if (wxTheApp->OnInit()) wxTheApp->OnRun();
                wxTheApp->OnExit();
                _windows.clear();
                wxEntryCleanup();
            }
        }

        UIWindow* NewWindow(const char* title) override {
            auto window =
                std::make_unique<Window>(title, [this]() { _wxApplication->ExitMainLoop(); });
            auto id = window->GetId();
            window->SetTitle(title);
            _windows[id] = std::move(window);
            return _windows[id].get();
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
