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
        std::unique_ptr<nana::form>       _nanaForm{};

    public:
        Window() { _nanaForm = std::make_unique<nana::form>(); }

        std::unique_ptr<nana::form>& GetNanaForm() { return _nanaForm; }

        bool Show() override {
            _nanaForm->show();
            return true;
        }

        bool SetTitle(const char* title) override {
            _nanaForm->caption(title);
            return true;
        }

        UITab* AddTab(const char* tabTitle) override { return nullptr; }

        UILabel*   AddLabel(const char* text) override { return nullptr; }
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
        void Run() override {
            // auto  window = std::make_unique<Window>();
            // auto& fm     = *window->GetNanaForm();
            // _windows.push_back(std::move(window));

            // fm

            // nana::place   plc{fm};
            // nana::label   lb{fm, "CHANGED!"};
            // nana::textbox tb{fm, "Hello, World!"};
            // nana::slider  sl{fm};
            // plc.div("<vert stuff>");
            // plc["stuff"] << lb << tb << sl;
            // plc.collocate();
            // fm.show();
            nana::exec();
        }

        UIWindow* NewWindow(const char* title) override {
            auto window = std::make_unique<Window>();
            window->SetTitle(title);

            if (_windows.empty()) {
                window->GetNanaForm()->events().unload([]() { nana::API::exit_all(); });
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
