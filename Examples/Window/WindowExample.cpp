#include <Logging/Logging.h>
#include <UserInterface.h>
#include <UserInterface/Autodetect.h>

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication();
    auto* window = app->NewWindow("Some Window ID");
    window->SetTitle("Hello from the Example Title");

    // Make 2 tabs (UIWidgetsContainer)
    auto* tab1 = window->NewTab("Tab 1");

    // Add textbox to each (UIWidget)

    // Add button to each (UIButton)

    app->Run();
}
