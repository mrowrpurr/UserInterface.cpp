#include <Logging.h>
#include <UserInterface.h>

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui  = UserInferface::GetUIManager();
    auto* app = ui->CreateApplication();

    // Create a FLTK window
    auto* fltkWindow = ui->CreateWindow("fltk");

    // Show a Nana window
    // TODO

    // Try the autodetection
    // TODO

    app->RunWindow(fltkWindow);
}
