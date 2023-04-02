#pragma once

namespace UserInterface {

    struct UIApplication;

    struct UIWindow {
        virtual UIApplication* GetApplication()            = 0;
        virtual bool           Show()                      = 0;
        virtual bool           SetTitle(const char* title) = 0;
    };

    struct UIApplication {
        virtual UIWindow* NewWindow() = 0;
        virtual bool      Run()       = 0;
    };

    struct UIToolkit {
        virtual UIApplication* NewApplication() = 0;
    };

    struct UIToolkitRegistry {
        virtual bool        IsToolkitAvailable(const char* toolkitName)                  = 0;
        virtual UIToolkit*  GetToolkit(const char* toolkitName)                          = 0;
        virtual bool        RegisterToolkit(const char* toolkitName, UIToolkit* toolkit) = 0;
        virtual const char* GetDefaultToolkitName()                                      = 0;
        virtual bool        SetDefaultToolkitName(const char* toolkitName)               = 0;
    };

    struct UIAPI {
        virtual UIApplication*     NewApplication(const char* toolkitName) = 0;
        virtual UIToolkitRegistry* GetToolkitRegistry()                    = 0;
    };
}
