#pragma once

#include <UserInterface/Interfaces.h>
#include <wx/notebook.h>
#include <wx/wx.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace UserInterface::wxWidgets {

    namespace Impl {
        class wxWindowImpl : public wxFrame {
            std::unique_ptr<wxNotebook>           _notebook;
            std::vector<std::unique_ptr<wxPanel>> _notebookPanels;

        public:
            wxWindowImpl(const wxString& title)
                : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200)) {}

            void ConfigureForTabs() { _notebook = std::make_unique<wxNotebook>(this, wxID_ANY); }

            std::unique_ptr<wxPanel>& AddTab(const char* tabName) {
                _notebookPanels.emplace_back(std::make_unique<wxPanel>(_notebook.get(), wxID_ANY));
                _notebook->AddPage(_notebookPanels.back().get(), tabName);
                return _notebookPanels.back();
            }
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

    class Label : public UILabel {
        std::unique_ptr<wxStaticText> _label;

    public:
        Label(std::unique_ptr<wxStaticText> label) : _label(std::move(label)) {}
        void SetText(const char* text) { _label->SetLabelText(text); }
    };

    class Textbox : public UITextbox {
        std::unique_ptr<wxTextCtrl> _textbox;

    public:
        Textbox(std::unique_ptr<wxTextCtrl> textbox) : _textbox(std::move(textbox)) {}
        void SetText(const char* text) { _textbox->SetValue(text); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::unique_ptr<wxBoxSizer>&           _sizer;
        std::vector<std::unique_ptr<UIWidget>> _widgets;

    public:
        WidgetContainer(std::unique_ptr<wxBoxSizer>& sizer) : _sizer(sizer) {}
        std::unique_ptr<wxBoxSizer>&            GetImplContainer() { return _sizer; }
        std::vector<std::unique_ptr<UIWidget>>& GetWidgets() { return _widgets; }

        UILabel* AddLabel(const char* text) override {
            auto labelImpl =
                std::make_unique<wxStaticText>(_sizer->GetContainingWindow(), wxID_ANY, text);
            _sizer->Add(labelImpl.get(), 0, wxEXPAND | wxALL, 5);
            _widgets.emplace_back(std::make_unique<Label>(std::move(labelImpl)));
            return static_cast<UILabel*>(_widgets.back().get());
        }

        UITextbox* AddTextbox(const char* text) override {
            auto textbox = std::make_unique<wxTextCtrl>(_sizer->GetContainingWindow(), wxID_ANY);
            _sizer->Add(textbox.get(), 0, wxEXPAND | wxALL, 5);
            _widgets.emplace_back(std::make_unique<Textbox>(std::move(textbox)));
            return static_cast<UITextbox*>(_widgets.back().get());
        }
    };

    class Window;

    class Tab : public UITab, public WidgetContainer {
        std::string _title;
        // std::unique_ptr<wxBoxSizer>&                               _sizer;
        // std::unordered_map<std::string, std::unique_ptr<UIWidget>> _widgets;
        // std::unique_ptr<WidgetContainer>                           _container;

    public:
        // Tab(const char* title, std::unique_ptr<wxBoxSizer>& sizer) : _title(title), _sizer(sizer)
        // {
        //     _container = std::make_unique<WidgetContainer>(_sizer);
        // }

        Tab(const char* title, std::unique_ptr<wxBoxSizer>& sizer) : WidgetContainer(sizer) {
            _title = title;
        }

        const char* GetTitle() override { return _title.c_str(); }
        void        SetTitle(const char* title) override { _title = title; }
    };

    class Window : public UIWindow, public WidgetContainer {
        std::shared_ptr<Impl::wxWindowImpl> _impl;
        std::vector<std::unique_ptr<Tab>>   _tabs;
        std::unique_ptr<wxBoxSizer>         _sizer;

    public:
        Window(std::shared_ptr<Impl::wxWindowImpl> impl, std::unique_ptr<wxBoxSizer> sizer)
            : WidgetContainer(_sizer), _impl(impl), _sizer(std::move(sizer)) {}

        bool Show() override {
            _impl->Show(true);
            return true;
        }

        bool SetTitle(const char* title) override {
            _impl->SetTitle(title);
            return true;
        }

        UITab* AddTab(const char*) override {
            // _impl->ConfigureForTabs();
            // _tabs.emplace_back(std::make_unique<Tab>(title, _impl->AddTab(title)));
            // return _tabs.back().get();
            return nullptr;
        }

        UILabel*   AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UITextbox* AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
    };

    class Application : public UIApplication {
        Impl::wxApplicationImpl*             _impl;  // wxWidgets responsible for the destruction
        std::vector<std::unique_ptr<Window>> _windows;

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

        UIWindow* NewWindow(const char* title) override {
            if (_windows.empty()) {
                auto mainWindow = _impl->GetMainWindow();
                mainWindow->SetTitle(title);
                auto sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);
                mainWindow->SetSizer(sizer.get());
                _windows.emplace_back(std::make_unique<Window>(mainWindow, std::move(sizer)));
            } else {
                auto windowImpl = std::make_shared<Impl::wxWindowImpl>(title);
                auto sizer      = std::make_unique<wxBoxSizer>(wxVERTICAL);
                windowImpl->SetSizer(sizer.get());
                _windows.emplace_back(std::make_unique<Window>(windowImpl, std::move(sizer)));
            }
            return _windows.back().get();
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
