#pragma once

namespace UserInterface {

    struct UIApplication;

    struct UIWidget {
        virtual ~UIWidget() = default;
    };

    struct UIButton : public UIWidget {};
    struct UILabel : public UIWidget {};
    struct UITextbox : public UIWidget {};

    struct UIWidgetContainer {
        virtual UILabel*   AddLabel(const char* text)   = 0;
        virtual UITextbox* AddTextbox(const char* text) = 0;
    };

    struct UITab : public UIWidgetContainer {
        virtual ~UITab()                                = default;
        virtual const char* GetTitle()                  = 0;
        virtual void        SetTitle(const char* title) = 0;
    };

    struct UIWindow : public UIWidgetContainer {
        virtual ~UIWindow()                        = default;
        virtual bool   Show()                      = 0;
        virtual bool   SetTitle(const char* title) = 0;
        virtual UITab* AddTab(const char* title)   = 0;
    };

    struct UIApplication {
        virtual ~UIApplication()                       = default;
        virtual UIWindow* NewWindow(const char* title) = 0;
        virtual void      Run()                        = 0;
    };

    struct UIToolkit {
        virtual ~UIToolkit()                    = default;
        virtual UIApplication* GetApplication() = 0;
    };

    struct UIToolkitRegistry {
        virtual size_t      GetToolkitCount()                                            = 0;
        virtual bool        IsToolkitAvailable(const char* toolkitName)                  = 0;
        virtual UIToolkit*  GetToolkit(const char* toolkitName)                          = 0;
        virtual bool        RegisterToolkit(const char* toolkitName, UIToolkit* toolkit) = 0;
        virtual const char* GetDefaultToolkitName()                                      = 0;
        virtual bool        SetDefaultToolkitName(const char* toolkitName)               = 0;
    };

    struct UIAPI {
        virtual UIApplication*     GetApplication()                        = 0;
        virtual UIApplication*     GetApplication(const char* toolkitName) = 0;
        virtual UIToolkitRegistry* GetToolkitRegistry()                    = 0;
    };
}
