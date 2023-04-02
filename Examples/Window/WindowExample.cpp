#include <Logging/Logging.h>
#include <UserInterface.h>
#include <UserInterface/Autodetect.h>

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication();
    auto* window = app->NewWindow("");
    window->SetTitle("Hello from the Example Title");

    // Add a label, textbox, and button to the window
    window->AddLabel("Hi, I am a label!");

    // hmmm
    window->AddTextbox("Butts.");

    // Make 2 tabs (UIWidgetsContainer)
    // auto* tab1 = window->AddTab("Tab 1");
    // auto* tab2 = window->AddTab("Tab 2");

    // Add a label to the first tab

    // Add a textbox and button to the second tab

    app->Run();
}
