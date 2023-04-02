#pragma once

namespace UserInterface {

    struct UIApplication;

    struct UIWidget {
        virtual ~UIWidget()         = default;
        virtual const char* GetId() = 0;
    };

    struct UIButton : public UIWidget {};

    struct UITab {
        virtual ~UITab()                                                            = default;
        virtual const char* GetId()                                                 = 0;
        virtual const char* GetTitle()                                              = 0;
        virtual void        SetTitle(const char* title)                             = 0;
        virtual UIWidget*   AddWidget(const char* widgetType, const char* widgetId) = 0;
    };

    struct UIWindow {
        virtual ~UIWindow()                                                 = default;
        virtual const char* GetId()                                         = 0;
        virtual bool        Show()                                          = 0;
        virtual bool        SetTitle(const char* title)                     = 0;
        virtual UITab*      NewTab(const char* tabId, const char* tabTitle) = 0;
        virtual UITab*      NewTab(const char* tabId) { return NewTab(tabId, tabId); }
        virtual UIWidget*   AddWidget(const char* widgetType, const char* widgetId) = 0;
    };

    struct UIApplication {
        virtual ~UIApplication()                          = default;
        virtual UIWindow* NewWindow(const char* windowId) = 0;
        virtual void      Run()                           = 0;
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
