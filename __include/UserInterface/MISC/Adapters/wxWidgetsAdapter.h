#pragma once

// // #include <Logging.h>
#include <wx/wx.h>

#include "../IToolkit.h"

namespace UserInterface::Adapters {

    class wxWidgetsAdapter : public IToolkit {
        class MyApp : public wxApp {
        public:
            virtual bool OnInit() {
                wxFrame* frame = new wxFrame(
                    NULL, wxID_ANY, "My Window Title", wxDefaultPosition, wxSize(300, 200)
                );
                frame->Show(true);
                return true;
            }
        };

    public:
        void RunWindow(Window* window) override {
            wxApp::SetInstance(new MyApp());

            int    argc = 0;
            char** argv = nullptr;
            wxEntryStart(argc, argv);

            if (!wxTheApp || !wxTheApp->CallOnInit()) return;
            wxTheApp->OnRun();
            wxTheApp->OnExit();
            wxEntryCleanup();
        }
    };
}
