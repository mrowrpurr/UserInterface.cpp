#include <Logging/Logging.h>
#include <UserInterface.h>
#include <UserInterface/RegisterToolkit.h>

//
// #include <UserInterface/wxWidgets.h>
// RegisterToolkit(wxWidgets, UserInterface::wxWidgets::Toolkit);

//
// #include <UserInterface/FLTK.h>
// RegisterToolkit(FLTK, UserInterface::FLTK::Toolkit);

//
#include <UserInterface/Qt.h>
RegisterToolkit(Qt, UserInterface::Qt::Toolkit);

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication("Qt");
    auto* window = app->NewWindow("Some Window ID");
    window->SetTitle("Hello World");
    app->Run();
}
