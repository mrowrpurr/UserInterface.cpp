#pragma once

#include <UserInterface/Interfaces.h>

#include <QApplication>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace UserInterface::Qt {

    class Label : public UILabel {
        QLabel      _label;
        std::string _text;

    public:
        Label() = default;
        Label(const char* text) : _label(text) {}
        QLabel*     GetLabelImpl() { return &_label; }
        void        SetText(const char* text) { _label.setText(text); }
        const char* GetText() {
            _text = _label.text().toStdString();
            return _text.c_str();
        }
    };

    class Textbox : public UITextbox {
        QLineEdit   _textbox;
        std::string _text;

    public:
        Textbox() = default;
        Textbox(const char* text) : _textbox(text) {}
        QLineEdit* GetTextboxImpl() { return &_textbox; }
        void       SetText(const char* text) {
            _textbox.setText(text);
            _textbox.setCursorPosition(0);
        }
        const char* GetText() {
            _text = _textbox.text().toStdString();
            return _text.c_str();
        }
    };

    class Button : public UIButton {
        QPushButton _button;
        std::string _text;

    public:
        Button() = default;
        Button(const char* text, void (*callback)()) : _button(text) {
            QObject::connect(&_button, &QPushButton::clicked, [=]() { callback(); });
        }
        QPushButton* GetButtonImpl() { return &_button; }
        void         SetText(const char* text) { _button.setText(text); }
        const char*  GetText() {
            _text = _button.text().toStdString();
            return _text.c_str();
        }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::string                            _fieldsPlaceString;
        std::vector<std::unique_ptr<UIWidget>> _widgets;
        QBoxLayout*                            _layout;

    public:
        WidgetContainer(QBoxLayout* layout) : _layout(layout) {}

        void Clear() { _widgets.clear(); }

        UILabel* AddLabel(const char* text) override {
            auto label = std::make_unique<Label>(text);
            _layout->addWidget(label->GetLabelImpl());
            _widgets.push_back(std::move(label));
            return static_cast<UILabel*>(_widgets.back().get());
        }
        UITextbox* AddTextbox(const char* text) override {
            auto textbox = std::make_unique<Textbox>(text);
            _layout->addWidget(textbox->GetTextboxImpl());
            _widgets.push_back(std::move(textbox));
            return static_cast<UITextbox*>(_widgets.back().get());
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            auto button = std::make_unique<Button>(text, callback);
            _layout->addWidget(button->GetButtonImpl());
            _widgets.push_back(std::move(button));
            return static_cast<UIButton*>(_widgets.back().get());
        }
    };

    class Window;

    class Tab : public WidgetContainer, public UITab {
        std::string _title;
        // nana::panel<true> _nanaPanel;
        // nana::place       _nanaPlace;
        // nana::place*      _windowPlace;

    public:
        // Tab(nana::form* nanaForm, nana::place* windowPlace, const char* title)
        //     : WidgetContainer("fields", &_nanaPanel, &_nanaPlace),
        //       _title(title),
        //       _nanaPanel(*nanaForm),
        //       _nanaPlace(_nanaPanel),
        //       _windowPlace(windowPlace) {
        //     _nanaPlace.div("vert <vert fields gap=5 arrange=[25,repeated]>");
        // }

        // nana::panel<true>* GetNanaPanel() { return &_nanaPanel; }
        void Show() {}
        void Hide() {}

        const char* GetTitle() override { return _title.c_str(); }
        void        SetTitle(const char*) override {}
        UILabel*    AddLabel(const char* text) override { return WidgetContainer::AddLabel(text); }
        UITextbox*  AddTextbox(const char* text) override {
            return WidgetContainer::AddTextbox(text);
        }
        UIButton* AddButton(const char* text, void (*callback)()) override {
            return WidgetContainer::AddButton(text, callback);
        }
    };

    class Window : public WidgetContainer, public UIWindow {
        std::vector<std::unique_ptr<Tab>> _tabs;
        QWidget                           _qtWindow;
        QVBoxLayout                       _qtLayout{&_qtWindow};

    public:
        Window() : WidgetContainer(&_qtLayout) {}
        ~Window() { Clear(); }

        bool Show() override {
            _qtWindow.show();
            return true;
        }

        bool SetTitle(const char* title) override {
            _qtWindow.setWindowTitle(title);
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            //
            return nullptr;
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
        int                                  _qtApplicationArgc = 0;
        char**                               _qtApplicationArgv = nullptr;
        std::unique_ptr<QApplication>        _qtApplication;

    public:
        Application() : _qtApplication(new QApplication(_qtApplicationArgc, _qtApplicationArgv)) {}

        void Run() override {
            _qtApplication->exec();
            _windows.clear();
            _qtApplication.reset();
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
