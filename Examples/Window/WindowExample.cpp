#include <Logging.h>
#include <UserInterface.h>

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui           = UserInterface::GetAPI();
    auto  wxRegistered = ui->GetToolkitRegistry()->IsToolkitAvailable("wxWidgets");
    Log("wxWidgets toolkit registered: {}", wxRegistered);
    // auto* app = ui->NewApplication("wxWidgets");
    //     auto* window = app->NewWindow();
    // return 0;
}
