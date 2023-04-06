#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // int main(int argc, char** argv) {
    Fl_Window win(500, 300, "FLTK Sample");
    win.begin();

    Fl_Tabs tabs(0, 0, 500, 300);
    tabs.begin();

    // First tab
    Fl_Group tab1(0, 30, 500, 270, "Form");
    tab1.begin();

    Fl_Box   name_label(10, 50, 100, 25, "Name:");
    Fl_Input name_input(120, 50, 200, 25);

    Fl_Box       age_label(10, 100, 100, 25, "Age:");
    Fl_Int_Input age_input(120, 100, 200, 25);

    tab1.end();

    // Second tab
    Fl_Group tab2(0, 30, 500, 270, "Controls");
    tab2.begin();

    Fl_Box    slider_label(10, 50, 100, 25, "Slider:");
    Fl_Slider slider(120, 50, 200, 25);

    Fl_Box          radio_label(10, 100, 100, 25, "Radio Group:");
    Fl_Round_Button radio1(120, 100, 100, 25, "Option 1");
    Fl_Round_Button radio2(230, 100, 100, 25, "Option 2");

    Fl_Box          checkbox_label(10, 150, 100, 25, "Checkbox:");
    Fl_Check_Button checkbox(120, 150, 100, 25, "Enable");

    tab2.end();

    tabs.end();
    win.end();
    win.show();
    // win.show(argc, argv);

    return Fl::run();
}
