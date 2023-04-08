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
            std::vector<std::function<void()>>       _onCloseCallbacks;
            std::unique_ptr<wxBoxSizer>              _sizer;
            std::unique_ptr<wxNotebook>              _notebook;
            std::vector<std::unique_ptr<wxPanel>>    _notebookPagePanels;
            std::vector<std::unique_ptr<wxBoxSizer>> _notebookPageSizers;

        public:
            wxWindowImpl(const wxString& title)
                : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200)),
                  _sizer(std::make_unique<wxBoxSizer>(wxVERTICAL)) {
                Bind(wxEVT_CLOSE_WINDOW, &wxWindowImpl::OnClose, this);
                SetSizer(_sizer.get());
            }

            void AddOnCloseCallback(std::function<void()> callback) {
                _onCloseCallbacks.push_back(callback);
            }

            std::unique_ptr<wxNotebook>& GetNotebook() { return _notebook; }

            void OnClose(wxCloseEvent&) {
                for (size_t i = 0; i < _notebookPageSizers.size(); i++) {
                    _notebookPagePanels[i]->SetSizer(nullptr, false);
                    _notebookPageSizers[i]->GetChildren().clear();
                    _notebookPageSizers[i]->Clear(false);
                }
                SetSizer(nullptr, false);
                _sizer->GetChildren().clear();
                for (auto& callback : _onCloseCallbacks) callback();
                Hide();
            }

            void ConfigureTabs() {
                if (_notebook) return;
                _notebook = std::make_unique<wxNotebook>(this, wxID_ANY);
                _sizer->Add(_notebook.get(), 1, wxEXPAND);
            }

            std::unique_ptr<wxBoxSizer>& AddTab(const char* tabName) {
                ConfigureTabs();
                auto panel = std::make_unique<wxPanel>(_notebook.get(), wxID_ANY);
                auto sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);
                panel->SetSizer(sizer.get());
                _notebook->AddPage(panel.get(), tabName);
                _notebookPagePanels.push_back(std::move(panel));
                _notebookPageSizers.push_back(std::move(sizer));
                return _notebookPageSizers.back();
            }

            std::unique_ptr<wxBoxSizer>& GetSizer() { return _sizer; }
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
        wxStaticText _wxLabel;

    public:
        Label(wxWindow* window, const std::string& text) : _wxLabel(window, wxID_ANY, text) {}
        wxStaticText& GetWxLabel() { return _wxLabel; }
        void          SetText(const char* text) {
            _wxLabel.SetLabel(text);
            _wxLabel.Refresh();
        }
        const char* GetText() { return _wxLabel.GetLabel().c_str(); }
    };

    class Textbox : public UITextbox {
        wxTextCtrl _wxTextbox;

    public:
        Textbox(wxWindow* window, const std::string& text) : _wxTextbox(window, wxID_ANY, text) {}
        wxTextCtrl& GetWxTextbox() { return _wxTextbox; }
        void        SetText(const char* text) {
            _wxTextbox.SetValue(text);
            _wxTextbox.Refresh();
        }
        const char* GetText() { return _wxTextbox.GetValue().c_str(); }
    };

    class Button : public UIButton {
        wxButton _wxButton;

    public:
        Button(wxWindow* window, const std::string& text, std::function<void()> callback)
            : _wxButton(window, wxID_ANY, text) {
            _wxButton.Bind(wxEVT_BUTTON, [callback](wxCommandEvent& event) { callback(); });
        }
        wxButton& GetWxButton() { return _wxButton; }
        void      SetText(const char* text) {
            _wxButton.SetLabel(text);
            _wxButton.Refresh();
        }
        const char* GetText() { return _wxButton.GetLabel().c_str(); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::vector<std::unique_ptr<UIWidget>> _widgets;
        wxBoxSizer*                            _sizer;

    public:
        void SetSizer(wxBoxSizer* sizer) { _sizer = sizer; }

        void Clear() {
            _widgets.clear();
            if (_sizer) _sizer->Clear(false);
        }

        UILabel* AddLabel(const char* text) override {
            if (!_sizer) return nullptr;
            auto label = std::make_unique<Label>(_sizer->GetContainingWindow(), text);
            _sizer->Add(&label->GetWxLabel(), 0, wxALL, 5);
            _widgets.push_back(std::move(label));
            return static_cast<UILabel*>(_widgets.back().get());
        }
        UITextbox* AddTextbox(const char* text) override {
            if (!_sizer) return nullptr;
            auto textbox = std::make_unique<Textbox>(_sizer->GetContainingWindow(), text);
            _sizer->Add(&textbox->GetWxTextbox(), 0, wxALL, 5);
            _widgets.push_back(std::move(textbox));
            return static_cast<UITextbox*>(_widgets.back().get());
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            if (!_sizer) return nullptr;
            auto button = std::make_unique<Button>(_sizer->GetContainingWindow(), text, callback);
            _sizer->Add(&button->GetWxButton(), 0, wxALL, 5);
            _widgets.push_back(std::move(button));
            return static_cast<UIButton*>(_widgets.back().get());
        }
    };

    class Window;

    class Tab : public WidgetContainer, public UITab {
        unsigned int _tabIndex;
        wxNotebook*  _notebook;
        std::string  _title;

    public:
        Tab(unsigned int tabIndex, wxNotebook* notebook, const char* title, wxBoxSizer* sizer)
            : _tabIndex(tabIndex), _notebook(notebook), _title(title) {
            SetSizer(sizer);
        }
        const char* GetTitle() override { return _title.c_str(); }
        void        SetTitle(const char* title) {
            _notebook->SetPageText(_tabIndex, title);
            _title = title;
        }
        UILabel*   AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UITextbox* AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
        }
    };

    class Window : public WidgetContainer, public UIWindow {
        unsigned int                        _height         = 100;
        unsigned int                        _width          = 100;
        bool                                _isVisible      = false;
        bool                                _appInitialized = false;
        std::vector<std::function<void()>>  _onInitCallbacks;
        std::function<void()>               _onCloseCallback;
        std::vector<std::unique_ptr<Tab>>   _tabs;
        std::unique_ptr<Impl::wxWindowImpl> _wxWindow;

        void PerformOnInitOrNow(std::function<void()> callback) {
            if (_appInitialized) callback();
            else _onInitCallbacks.push_back(callback);
        }

    public:
        Window(const std::string& title, std::function<void()> onCloseCallback)
            : _onCloseCallback(onCloseCallback),
              _wxWindow(std::make_unique<Impl::wxWindowImpl>(title)) {
            SetSizer(_wxWindow->GetSizer().get());
            _wxWindow->AddOnCloseCallback([this]() {
                for (auto& tab : _tabs) tab->Clear();
                Clear();
                _isVisible = false;
                if (_onCloseCallback) _onCloseCallback();
            });
            _wxWindow->ConfigureTabs();
        }

        std::unique_ptr<Impl::wxWindowImpl>& GetWxWindow() { return _wxWindow; }

        void OnInit() {
            _appInitialized = true;
            for (auto& callback : _onInitCallbacks) callback();
            _onInitCallbacks.clear();
        }

        bool Show() override {
            PerformOnInitOrNow([this]() {
                _wxWindow->Show(true);
                _isVisible = true;
            });
            return true;
        }

        bool Hide() override {
            _wxWindow->Show(false);
            _isVisible = false;
            return true;
        }

        bool IsVisible() { return _isVisible; }

        bool Close() override {
            Clear();
            _wxWindow->Close();
            return true;
        }

        bool SetTitle(const char* title) override {
            _wxWindow->SetTitle(title);
            return true;
        }

        bool SetHeight(unsigned int height) override {
            _wxWindow->SetSize(_width, height);
            _height = height;
            return true;
        }

        bool SetWidth(unsigned int width) override {
            _wxWindow->SetSize(width, _height);
            _width = width;
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            auto& tabSizer = _wxWindow->AddTab(tabTitle);
            auto  tab      = std::make_unique<Tab>(
                _tabs.size(), _wxWindow->GetNotebook().get(), tabTitle, tabSizer.get()
            );
            _tabs.push_back(std::move(tab));
            auto* tabPtr = _tabs.back().get();
            return tabPtr;
        }

        UILabel*   AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UITextbox* AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
        }
    };

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;
        Impl::wxApplicationImpl*             _wxApplication;

        void WindowClosedCallback() {
            size_t visibleWindows = 0;
            for (auto& window : _windows)
                if (window->IsVisible()) ++visibleWindows;
            if (visibleWindows == 0) _wxApplication->ExitMainLoop();
        }

    public:
        Application()
            : _wxApplication(new Impl::wxApplicationImpl([this]() {
                  for (auto& window : _windows) window->OnInit();
              })) {}

        void Run() override {
            wxApp::SetInstance(_wxApplication);

            int    argc = 0;
            char** argv = nullptr;
            if (wxEntryStart(argc, argv)) {
                if (wxTheApp->OnInit()) wxTheApp->OnRun();
                wxTheApp->OnExit();
                for (auto& window : _windows) window->Close();
                _windows.clear();
                wxEntryCleanup();
            }
        }

        UIWindow* NewWindow(const char* title) override {
            auto window = std::make_unique<Window>(title, [this]() { WindowClosedCallback(); });
            window->SetTitle(title);
            _windows.push_back(std::move(window));
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
