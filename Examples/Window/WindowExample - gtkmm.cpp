#include <gtk/gtk.h>
#include <gtkmm.h>

#include <iostream>

//
// #include <Windows.h>

// class SimpleWindow : public Gtk::ApplicationWindow {
// public:
//     SimpleWindow() {
//         set_title("Simple Gtkmm App");
//         set_default_size(200, 100);

//         button.set_label("Click me!");
//         button.signal_clicked().connect(sigc::mem_fun(*this, &SimpleWindow::on_button_click));

//         set_child(button);
//         button.show();
//     }

// protected:
//     void on_button_click() { std::cout << "Button clicked!" << std::endl; }

//     Gtk::Button button;
// };

// class SimpleApp : public Gtk::Application {
// protected:
//     Glib::RefPtr<Gtk::ApplicationWindow> create_window() {
//         return Glib::make_refptr_for_instance<SimpleWindow>(new SimpleWindow());
//     }
// };

#include <gtkmm/button.h>
#include <gtkmm/window.h>

// class HelloWorld : public Gtk::Window {
// public:
//     HelloWorld();
//     ~HelloWorld() override;

// protected:
//     // Signal handlers:
//     void on_button_clicked();

//     // Member widgets:
//     Gtk::Button m_button;
// };

// // int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
// int main(int argc, char* argv[]) {
//     // auto app = Gtk::Application::create("com.mp.HelloWorld");
//     // return app->make_window_and_run<HelloWorld>(argc, argv);
//     auto app = Gtk::Application::create(argc, argv, "");
// }

class Win : public Gtk::Window {
public:
    Win();
};

Win::Win() {
    set_title("Hello world");
    set_default_size(500, 500);
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<Win>(argc, argv);
}
