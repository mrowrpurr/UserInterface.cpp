#include <Logging/Logging.h>
#include <UserInterface.h>
#include <UserInterface/RegisterToolkit.h>
#include <UserInterface/wxWidgets.h>

RegisterToolkit(wxWidgets, UserInterface::wxWidgets::Toolkit);

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication("wxWidgets");
    auto* window = app->NewWindow("Some Window ID");
    window->SetTitle("Hello World");
    app->Run();
}
