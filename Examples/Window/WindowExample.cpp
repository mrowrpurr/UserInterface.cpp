#include <Logging/Logging.h>
#include <UserInterface.h>
#include <UserInterface/Autodetect.h>

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication();
    auto* window = app->NewWindow("Some Window ID");
    window->SetTitle("Hello World");
    app->Run();
}
