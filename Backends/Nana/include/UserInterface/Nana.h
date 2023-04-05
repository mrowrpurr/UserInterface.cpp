#pragma once

#include <UserInterface/Interfaces.h>

#include <memory>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
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
        nana::label _nanaLabel;

    public:
        Label(nana::panel<true>* nanaPanel) : _nanaLabel(*nanaPanel) {}

        nana::label* GetNanaLabel() { return &_nanaLabel; }
        void         SetText(const char* text) { _nanaLabel.caption(text); }
        const char*  GetText() { return nullptr; }
    };

    class Textbox : public UITextbox {
        nana::textbox _nanaTextbox;

    public:
        Textbox(nana::panel<true>* nanaPanel) : _nanaTextbox(*nanaPanel) {}

        nana::textbox* GetNanaTextbox() { return &_nanaTextbox; }
        void           SetText(const char* text) { _nanaTextbox.caption(text); }
        const char*    GetText() { return nullptr; }
    };

    class Button : public UIButton {
        nana::button _nanaButton;

    public:
        Button(std::unique_ptr<nana::panel<true>>& nanaPanel) : _nanaButton(*nanaPanel) {}

        void SetText(const char* text) { _nanaButton.caption(text); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::string                                             _fieldsPlaceString = "fields";
        std::unique_ptr<std::vector<std::unique_ptr<UIWidget>>> _widgets;
        nana::panel<true>*                                      _nanaPanel;
        nana::place*                                            _nanaPanelPlace;

    public:
        WidgetContainer(
            const std::string& fieldsPlaceString, nana::panel<true>* nanaPanel,
            nana::place* nanaPanelPlace
        )
            : _fieldsPlaceString(fieldsPlaceString),
              _widgets(std::make_unique<std::vector<std::unique_ptr<UIWidget>>>()),
              _nanaPanel(nanaPanel),
              _nanaPanelPlace(nanaPanelPlace) {}

        UILabel* AddLabel(const char* text) override {
            auto* label = new Label(_nanaPanel);
            label->SetText(text);
            _nanaPanelPlace->field(_fieldsPlaceString.c_str()) << *label->GetNanaLabel();
            _nanaPanelPlace->collocate();
            _widgets->push_back(std::unique_ptr<UIWidget>(label));
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            auto* textbox = new Textbox(_nanaPanel);
            textbox->SetText(text);
            _nanaPanelPlace->field(_fieldsPlaceString.c_str()) << *textbox->GetNanaTextbox();
            _nanaPanelPlace->collocate();
            _widgets->push_back(std::unique_ptr<UIWidget>(textbox));
            return textbox;
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            // auto* button = new Button(_nanaPanel);
            // button->SetText(text);
            // _widgets.push_back(std::unique_ptr<UIWidget>(button));
            // // TODO
            // _nanaPanelPlace->collocate();
            // return button;
            return nullptr;
        }
    };

    class Window;

    class Tab : public WidgetContainer, public UITab {
        std::string _title;

    public:
        Tab() : WidgetContainer("fields", nullptr, nullptr) {}

        const char* GetTitle() override {
            // Nothing setup to give access here... let's fix this later!
            return nullptr;
        }
        void SetTitle(const char* title) override {
            // TODO make SetTitle return a bool, cause you can't do it with Nana... well, not easily
            // at least.
        }
        UILabel* AddLabel(const char* text) override {
            auto* label = WidgetContainer::AddLabel(text);
            //
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
        }
    };

    class Window : public WidgetContainer, public UIWindow {
        std::vector<std::unique_ptr<Tab>> _tabs;
        nana::form                        _nanaForm{};
        nana::place                       _nanaMainPlace{_nanaForm};
        nana::panel<true>                 _nanaWindowWidgetsPanel{_nanaForm};
        nana::place                       _nanaWindowWidgetsPlace{_nanaWindowWidgetsPanel};

    public:
        Window() : WidgetContainer("fields", &_nanaWindowWidgetsPanel, &_nanaWindowWidgetsPlace) {
            _nanaMainPlace.div("vert <mainWidgetsPanel>");
            _nanaMainPlace.field("mainWidgetsPanel") << _nanaWindowWidgetsPanel;
            _nanaMainPlace.collocate();
            _nanaWindowWidgetsPlace.div("vert <vert fields max=50 gap=5>");
        }

        nana::form* GetNanaForm() { return &_nanaForm; }

        bool Show() override {
            _nanaForm.show();
            return true;
        }

        bool SetTitle(const char* title) override { return true; }

        UITab* AddTab(const char* tabTitle) override { return nullptr; }

        UILabel* AddLabel(const char* text) override {
            auto* label = WidgetContainer::AddLabel(text);
            _nanaWindowWidgetsPlace.collocate();
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            auto* textbox = WidgetContainer::AddTextbox(text);
            _nanaWindowWidgetsPlace.collocate();
            return textbox;
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            auto* button = WidgetContainer::AddButton(text, callback);
            _nanaWindowWidgetsPlace.collocate();
            return button;
        }
    };

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;

    public:
        void Run() override {
            nana::exec();
            _windows.clear();
            nana::API::exit_all();
        }

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
