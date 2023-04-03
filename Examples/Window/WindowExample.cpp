#include <Logging/Logging.h>
#include <UserInterface.h>
#include <UserInterface/Autodetect.h>

SetLogFilePath("C:/temp/UserInterfaceExample.log");

UserInterface::UITextbox* textbox      = nullptr;
UserInterface::UITextbox* tab1_textbox = nullptr;
UserInterface::UITextbox* tab2_textbox = nullptr;

UI_Main {
    auto* ui     = UserInterface::GetAPI();
    auto* app    = ui->GetApplication();
    auto* window = app->NewWindow("");
    window->SetTitle("????");

    // auto* tab1 = window->AddTab("Tab 1");
    // auto* tab2 = window->AddTab("Tab 2");

    // tab1->AddLabel("Tab 1 label!");
    // tab1_textbox = tab1->AddTextbox("Tab 1 textbox.");
    // tab1->AddButton("Tab 1 button", []() { tab1_textbox->SetText("The button was pressed!"); });

    // tab2->AddLabel("Butts!");
    // tab2_textbox = tab2->AddTextbox("Butts.");
    // tab2->AddButton("I am BUTTS! CLICK ME", []() {
    //     tab2_textbox->SetText("The BUTTS was pressed!");
    // });

    window->AddLabel("Hi, I am a label!");
    window->Show();
    // textbox = window->AddTextbox("Butts.");
    // window->AddButton("I am button! CLICK ME", []() {
    //     textbox->SetText("The button was pressed!");
    // });

    app->Run();
}
