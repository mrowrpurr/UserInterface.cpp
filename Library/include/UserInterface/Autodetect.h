#include <UserInterface/RegisterToolkit.h>

#if __has_include(<QApplication>)
    #include <UserInterface/Qt.h>
UserInterface_RegisterToolkit(Qt, UserInterface::Qt::Toolkit);
#endif

#if __has_include(<wx/wx.h>)
    #include <UserInterface/wxWidgets.h>
UserInterface_RegisterToolkit(wxWidgets, UserInterface::wxWidgets::Toolkit);
#endif

#if __has_include(<FL/Fl.h>)
    #include <UserInterface/FLTK.h>
UserInterface_RegisterToolkit(FLTK, UserInterface::FLTK::Toolkit);
#endif

#if __has_include(<nana/gui.hpp>)
    #include <UserInterface/Nana.h>
UserInterface_RegisterToolkit(Nana, UserInterface::Nana::Toolkit);
#endif
