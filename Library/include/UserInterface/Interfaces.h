#pragma once

namespace UserInterface {

    struct UIApplication;

    struct UIWindow {
        virtual const char*    GetId()                     = 0;
        virtual UIApplication* GetApplication()            = 0;
        virtual bool           Show()                      = 0;
        virtual bool           SetTitle(const char* title) = 0;
    };

    struct UIApplication {
        virtual UIWindow* NewWindow(const char* windowId) = 0;
        virtual void      Run()                           = 0;
    };

    struct UIToolkit {
        virtual UIApplication* GetApplication() = 0;
    };

    struct UIToolkitRegistry {
        virtual bool        IsToolkitAvailable(const char* toolkitName)                  = 0;
        virtual UIToolkit*  GetToolkit(const char* toolkitName)                          = 0;
        virtual bool        RegisterToolkit(const char* toolkitName, UIToolkit* toolkit) = 0;
        virtual const char* GetDefaultToolkitName()                                      = 0;
        virtual bool        SetDefaultToolkitName(const char* toolkitName)               = 0;
    };

    struct UIAPI {
        virtual UIApplication*     GetApplication(const char* toolkitName) = 0;
        virtual UIToolkitRegistry* GetToolkitRegistry()                    = 0;
    };
}
