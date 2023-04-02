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
// #include <UserInterface/Qt.h>
// RegisterToolkit(Qt, UserInterface::Qt::Toolkit);

//
#include <UserInterface/Nana.h>
RegisterToolkit(Nana, UserInterface::Nana::Toolkit);

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication("nana");
    auto* window = app->NewWindow("Some Window ID");
    window->SetTitle("Hello World");
    app->Run();
}
