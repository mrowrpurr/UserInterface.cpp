#include "RegisterToolkit.h"

#if __has_include(<QApplication>) && __has_include(<UserInterface/Qt.h>)
    #include <UserInterface/Qt.h>
UserInterface_RegisterToolkit(Qt, UserInterface::Qt::Toolkit);
#endif

#if __has_include(<wx/wx.h>) && __has_include(<UserInterface/wxWidgets.h>)
    #include <UserInterface/wxWidgets.h>
UserInterface_RegisterToolkit(wxWidgets, UserInterface::wxWidgets::Toolkit);
#endif

#if __has_include(<FL/Fl.h>) && __has_include(<UserInterface/FLTK.h>)
    #include <UserInterface/FLTK.h>
UserInterface_RegisterToolkit(FLTK, UserInterface::FLTK::Toolkit);
#endif

#if __has_include(<nana/gui.hpp>) && __has_include(<UserInterface/Nana.h>)
    #include <UserInterface/Nana.h>
UserInterface_RegisterToolkit(Nana, UserInterface::Nana::Toolkit);
#endif
