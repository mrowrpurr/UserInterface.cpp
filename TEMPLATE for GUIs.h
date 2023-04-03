#pragma once

#include <UserInterface/Interfaces.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace UserInterface::Qt {

    namespace Impl {}

    class Label : public UILabel {
        // std::unique_ptr<wxStaticText> _label;

    public:
        // Label(std::unique_ptr<wxStaticText> label) : _label(std::move(label)) {}
        void        SetText(const char* text) {}
        const char* GetText() { return nullptr; }
    };

    class Textbox : public UITextbox {
        // std::unique_ptr<wxTextCtrl> _textbox;

    public:
        // Textbox(std::unique_ptr<wxTextCtrl> textbox) : _textbox(std::move(textbox)) {}
        void        SetText(const char* text) {}
        const char* GetText() { return nullptr; }
    };

    class Button : public UIButton {
        // std::unique_ptr<wxButton> _button;
        // void (*_callback)() = nullptr;

    public:
        // Button(std::unique_ptr<wxButton> button) : _button(std::move(button)) {}
        // Button(std::unique_ptr<wxButton> button, void (*callback)())
        // : _button(std::move(button)), _callback(callback) {
        // _button->Bind(wxEVT_BUTTON, &Button::TriggerOnClick, this);
        // }
        void SetText(const char* text) {}
        // void TriggerOnClick(wxCommandEvent&) { _callback(); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::vector<std::unique_ptr<UIWidget>> _widgets;

    public:
        WidgetContainer() = default;
        std::vector<std::unique_ptr<UIWidget>>& GetWidgets() { return _widgets; }

        UILabel*   AddLabel(const char* text) override { return nullptr; }
        UITextbox* AddTextbox(const char* text) override { return nullptr; }
        UIButton*  AddButton(const char* text, void (*callback)()) override { return nullptr; }
    };

    class Window;

    class Tab : public UITab, public WidgetContainer {
        std::string _title;

    public:
        Tab() : WidgetContainer() {}

        const char* GetTitle() override { return _title.c_str(); }
        void        SetTitle(const char* title) override { _title = title; }
        UILabel*    AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UITextbox*  AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
        }
    };

    class Window : public UIWindow, public WidgetContainer {
        std::vector<std::unique_ptr<Tab>> _tabs;

    public:
        bool Show() override {
            // _impl->Show(true);
            return true;
        }

        bool SetTitle(const char* title) override {
            // _impl->SetTitle(title);
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            // auto* wxBoxSizer = _impl->AddTab(tabTitle);
            // _tabs.emplace_back(std::make_unique<Tab>(wxBoxSizer));
            // return _tabs.back().get();
            return nullptr;
        }
        UILabel* AddLabel(const char* text) override {
            // SetSizer(_impl->SetupMainSizer());
            // return WidgetContainer::AddLabel(text);
            return nullptr;
        }
        UITextbox* AddTextbox(const char* text) override {
            // SetSizer(_impl->SetupMainSizer());
            // return WidgetContainer::AddTextbox(text);
            return nullptr;
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            // SetSizer(_impl->SetupMainSizer());
            // return WidgetContainer::AddButton(text, callback);
            return nullptr;
        }
    };

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;

    public:
        void Run() override {}

        UIWindow* NewWindow(const char* title) override { return nullptr; }
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
