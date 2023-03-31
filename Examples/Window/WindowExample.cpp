// #include <Logging.h>
#include <UserInterface.h>

// SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetUIManager();
    auto* app    = ui->NewApplication();
    auto* window = ui->NewWindow();
    app->RunWindow(window, "fltk");
    app->RunWindow(window, "nana");
    app->RunWindow(window, "wxwidgets");
}
