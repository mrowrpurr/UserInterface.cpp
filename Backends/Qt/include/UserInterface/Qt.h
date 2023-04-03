#pragma once

#include <UserInterface/Interfaces.h>

#include <QApplication>
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
        std::unique_ptr<QLabel> _label;
        std::string             _text;

    public:
        Label(const char* text) : _label(std::make_unique<QLabel>(text)), _text(text) {}
        std::unique_ptr<QLabel>& GetLabelImpl() { return _label; }
        void                     SetText(const char* text) { _label->setText(text); }
        const char*              GetText() {
            _text = _label->text().toStdString();
            return _text.c_str();
        }
    };

    class Textbox : public UITextbox {
        QLineEdit*  _textbox;
        std::string _text;

    public:
        Textbox(const char* text) : _textbox(new QLineEdit(text)) { _text = text; }
        QLineEdit* GetTextboxImpl() { return _textbox; }
        void       SetText(const char* text) {
            _textbox->setText(text);
            _textbox->setCursorPosition(0);
        }
        const char* GetText() {
            _text = _textbox->text().toStdString();
            return _text.c_str();
        }
    };

    class Button : public UIButton {
        QPushButton* _button;
        void (*_callback)() = nullptr;

    public:
        Button(const char* text, void (*callback)()) : _button(new QPushButton(text)) {
            _callback = callback;
            QObject::connect(_button, &QPushButton::clicked, [=]() { _callback(); });
        }
        QPushButton* GetButtonImpl() { return _button; }
        void         SetText(const char* text) { _button->setText(text); }
    };

    class WidgetContainer : public UIWidgetContainer {
        std::unique_ptr<QVBoxLayout>&          _layout;
        std::vector<std::unique_ptr<UIWidget>> _widgets;

    public:
        WidgetContainer(std::unique_ptr<QVBoxLayout>& layout) : _layout(layout) {}

        std::vector<std::unique_ptr<UIWidget>>& GetWidgets() { return _widgets; }

        UILabel* AddLabel(const char* text) override {
            auto label = std::make_unique<Label>(text);
            _layout->addWidget(label->GetLabelImpl().get());
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

    class Tab : public UITab, public WidgetContainer {
        std::string                  _title;
        std::unique_ptr<QVBoxLayout> _layout;
        std::unique_ptr<QWidget>     _tabWidget;

    public:
        Tab()
            : WidgetContainer(_layout),
              _layout(std::make_unique<QVBoxLayout>()),
              _tabWidget(std::make_unique<QWidget>()) {
            _tabWidget->setLayout(_layout.get());
        }

        std::unique_ptr<QWidget>& GetTabWidget() { return _tabWidget; }

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
        QWidget                           _impl;
        std::unique_ptr<QVBoxLayout>      _layout;
        std::unique_ptr<QTabWidget>       _tabWidget;

        void InitTabs() {
            if (_tabWidget) return;
            _tabWidget = std::make_unique<QTabWidget>(&_impl);
            _layout->addWidget(_tabWidget.get());
        }

    public:
        Window()
            : WidgetContainer(_layout), _impl(), _layout(std::make_unique<QVBoxLayout>(&_impl)) {
            _impl.setLayout(_layout.get());
        }

        bool Show() override {
            _impl.show();
            return true;
        }

        bool SetTitle(const char* title) override {
            _impl.setWindowTitle(title);
            return true;
        }

        UITab* AddTab(const char* tabTitle) override {
            InitTabs();
            _tabs.emplace_back(std::make_unique<Tab>());
            _tabWidget->addTab(_tabs.back()->GetTabWidget().get(), tabTitle);
            return _tabs.back().get();
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
        std::unique_ptr<QApplication>        _impl;

    public:
        Application() {
            int    argc = 0;
            char** argv = nullptr;
            _impl       = std::make_unique<QApplication>(argc, argv);
        }

        void Run() override {
            int    argc = 0;
            char** argv = nullptr;
            _impl->exec();
        }

        UIWindow* NewWindow(const char* title) override {
            auto window = std::make_unique<Window>();
            auto result = window.get();
            _windows.emplace_back(std::move(window));
            return result;
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
