if(fltk IN_LIST VCPKG_MANIFEST_FEATURES)
    add_subdirectory(FLTK)
endif()

if(wxwidgets IN_LIST VCPKG_MANIFEST_FEATURES)
    add_subdirectory(wxWidgets)
endif()

if(qt IN_LIST VCPKG_MANIFEST_FEATURES)
    add_subdirectory(Qt)
endif()

# ###############################################
# ###############################################
# ###############################################
# ###############################################
# ###############################################
if(nana IN_LIST VCPKG_MANIFEST_FEATURES)
    # find_package(unofficial-nana CONFIG REQUIRED)
endif()

if(gtkmm IN_LIST VCPKG_MANIFEST_FEATURES)
    # find_package(PkgConfig REQUIRED)
    # pkg_check_modules(GTK4 REQUIRED gtk4)
    # pkg_check_modules(GTKMM gtkmm-4.0)
endif()

if(imgui-glfw3-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
    # find_package(imgui CONFIG REQUIRED)
    # find_package(OpenGL REQUIRED)
    # find_package(glfw3 CONFIG REQUIRED)
endif()

if(imgui-sdl2-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
    # find_package(imgui CONFIG REQUIRED)
    # find_package(OpenGL REQUIRED)
    # find_package(SDL2 CONFIG REQUIRED)
    # find_package(GLEW REQUIRED)
endif()