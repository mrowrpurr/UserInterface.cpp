#pragma once

#include <UserInterface/Interfaces.h>

#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace UserInterface::Nana {

    namespace Impl {}

    class Label : public UILabel {
        std::shared_ptr<nana::label> _label;

    public:
        Label(std::shared_ptr<nana::label> label) : _label(std::move(label)) {}
        std::shared_ptr<nana::label>& GetNanaWidget() { return _label; }
        void                          SetText(const char* text) { _label->caption(text); }
        const char*                   GetText() { return nullptr; }
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
        void SetText(const char* text) {}
    };

    class WidgetContainer : public UIWidgetContainer {
        std::vector<std::unique_ptr<UIWidget>> _widgets;

    public:
        std::vector<std::unique_ptr<UIWidget>>& GetWidgets() { return _widgets; }

        UILabel*   AddLabel(const char* text) override { return nullptr; }
        UITextbox* AddTextbox(const char* text) override { return nullptr; }
        UIButton*  AddButton(const char* text, void (*callback)()) override { return nullptr; }
    };

    class Window;

    class Tab : public UITab, public WidgetContainer {
        std::string _title;

    public:
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
        nana::form                        _nanaForm{};
        nana::panel<true>                 _nanaPanel{_nanaForm};
        nana::tabbar<std::string>         _tabbar{_nanaForm};
        std::vector<nana::panel<true>>    _tabPanels;

    public:
        bool Show() override {
            _nanaForm.show();
            return true;
        }

        bool SetTitle(const char* title) override {
            _nanaForm.caption(title);
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            //
            //
            //
            return nullptr;
        }

        std::shared_ptr<nana::panel<true>> panel;
        std::shared_ptr<nana::place>       place;
        std::shared_ptr<nana::label>       label;

        UILabel* AddLabel(const char* text) override {
            panel.reset(new nana::panel<true>{_nanaForm});
            place.reset(new nana::place{*panel});
            label.reset(new nana::label{*panel, "Hmmmmm"});

            place->div("vert <label>");
            place->field("label") << *label;
            place->collocate();

            // auto label = std::make_unique<Label>(std::make_shared<nana::label>(_nanaForm, text));
            // _widgets.push_back(std::move(label));
            // return static_cast<UILabel*>(_widgets.back().get());
            return nullptr;

            // return WidgetContainer::AddLabel(text);
        }
        UITextbox* AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
        }
    };

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;

    public:
        void Run() override { nana::exec(); }

        UIWindow* NewWindow(const char* title) override {
            auto window = std::make_unique<Window>();
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
