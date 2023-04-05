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
        std::unique_ptr<nana::label> _nanaLabel;

    public:
        Label(std::unique_ptr<nana::panel<true>>& nanaPanel)
            : _nanaLabel(std::make_unique<nana::label>(*nanaPanel)) {}
        std::unique_ptr<nana::label>& GetNanaLabel() { return _nanaLabel; }
        void                          SetText(const char* text) { _nanaLabel->caption(text); }
        const char*                   GetText() { return nullptr; }
    };

    class Textbox : public UITextbox {
        nana::textbox _nanaTextbox;

    public:
        Textbox(std::unique_ptr<nana::panel<true>>& nanaPanel) : _nanaTextbox(*nanaPanel) {}

        void        SetText(const char* text) { _nanaTextbox.caption(text); }
        const char* GetText() { return nullptr; }
    };

    class Button : public UIButton {
        nana::button _nanaButton;

    public:
        Button(std::unique_ptr<nana::panel<true>>& nanaPanel) : _nanaButton(*nanaPanel) {}

        void SetText(const char* text) { _nanaButton.caption(text); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::vector<std::unique_ptr<UIWidget>> _widgets;
        nana::form*                            _nanaForm;
        std::unique_ptr<nana::panel<true>>     _nanaPanel;
        std::unique_ptr<nana::place>           _nanaPanelPlace;

    public:
        WidgetContainer(nana::form* nanaForm) : _nanaForm(nanaForm) { SetNanaForm(nanaForm); }

        void SetNanaForm(nana::form* nanaForm) {
            _nanaForm = nanaForm;
            if (_nanaForm) {
                _nanaPanel      = std::make_unique<nana::panel<true>>(*_nanaForm);
                _nanaPanelPlace = std::make_unique<nana::place>(*_nanaPanel);
                _nanaPanelPlace->div("vert <fields>");
            }
        }

        std::unique_ptr<nana::panel<true>>& GetNanaPanel() { return _nanaPanel; }

        std::vector<std::unique_ptr<UIWidget>>& GetWidgets() { return _widgets; }

        UILabel* AddLabel(const char* text) override {
            auto* label = new Label(_nanaPanel);
            label->SetText(text);
            _widgets.push_back(std::unique_ptr<UIWidget>(label));
            _nanaPanelPlace->field("fields") << *label->GetNanaLabel();
            _nanaPanelPlace->collocate();
            return label;
        }
        UITextbox* AddTextbox(const char* text) override {
            auto* textbox = new Textbox(_nanaPanel);
            textbox->SetText(text);
            _widgets.push_back(std::unique_ptr<UIWidget>(textbox));
            // TODO
            _nanaPanelPlace->collocate();
            return textbox;
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            auto* button = new Button(_nanaPanel);
            button->SetText(text);
            _widgets.push_back(std::unique_ptr<UIWidget>(button));
            // TODO
            _nanaPanelPlace->collocate();
            return button;
        }
    };

    class Window;

    class Tab : public WidgetContainer, public UITab {
        std::string _title;

    public:
        Tab(nana::form* nanaForm) : WidgetContainer(nanaForm) {}

        const char* GetTitle() override {
            // Nothing setup to give access here... let's fix this later!
            return nullptr;
        }
        void SetTitle(const char* title) override {
            // TODO make SetTitle return a bool, cause you can't do it with Nana... well, not easily
            // at least.
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
        std::vector<std::unique_ptr<Tab>>          _tabs;
        std::unique_ptr<nana::form>                _nanaForm;
        std::unique_ptr<nana::place>               _nanaFormMainPlace;
        std::unique_ptr<nana::tabbar<std::string>> _nanaTabBar;

    public:
        Window()
            : WidgetContainer(nullptr),
              _nanaForm(std::make_unique<nana::form>()),
              _nanaFormMainPlace(std::make_unique<nana::place>(*_nanaForm)),
              _nanaTabBar(std::make_unique<nana::tabbar<std::string>>(*_nanaForm)) {
            SetNanaForm(_nanaForm.get());
            // _nanaFormMainPlace->div("vert <tabBar><tabPanels><mainPanel>"
            _nanaFormMainPlace->div("vert <mainPanel>");  // <--- pass the NAME of the <panel>
            _nanaFormMainPlace->field("mainPanel") << *GetNanaPanel();
            _nanaFormMainPlace->collocate();
        }

        nana::form& GetNanaForm() { return *_nanaForm; }

        bool Show() override {
            _nanaForm->show();
            return true;
        }

        bool SetTitle(const char* title) override {
            _nanaForm->caption(title);
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            if (_tabs.empty()) {
                _nanaFormMainPlace->field("tabBar") << *_nanaTabBar;
                _nanaFormMainPlace->collocate();
            }

            auto tab = std::make_unique<Tab>(_nanaForm.get());
            _nanaTabBar->push_back(tabTitle);
            _nanaFormMainPlace->field("tabPanels") << *tab->GetNanaPanel();

            _tabs.push_back(std::move(tab));
            return _tabs.back().get();
        }

        UILabel* AddLabel(const char* text) override {
            return WidgetContainer::AddLabel(text);
            _nanaFormMainPlace->collocate();
        }
        UITextbox* AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
            _nanaFormMainPlace->collocate();
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
            _nanaFormMainPlace->collocate();
        }
    };

    class Application : public UIApplication {
        std::vector<std::unique_ptr<Window>> _windows;

    public:
        void Run() override { nana::exec(); }

        UIWindow* NewWindow(const char* title) override {
            auto window = std::make_unique<Window>();
            window->SetTitle(title);

            if (_windows.empty()) {
                window->GetNanaForm().events().unload([]() { nana::API::exit_all(); });
                window->Show();
            }

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
