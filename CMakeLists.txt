cmake_minimum_required(VERSION 3.21)

project(UserInterface-Project LANGUAGES CXX)

# Logging library [at least temporarily...]
add_subdirectory("$ENV{LOGGING_LIBRARY}" "${CMAKE_CURRENT_BINARY_DIR}/LoggingLibrary")

if(nana IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(unofficial-nana CONFIG REQUIRED)
endif()

if(fltk IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(FLTK CONFIG REQUIRED)
endif()

if(wxwidgets IN_LIST VCPKG_MANIFEST_FEATURES)
endif()

if(imgui-glfw3-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(imgui CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
endif()

if(imgui-sdl2-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(imgui CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(GLEW REQUIRED)
endif()

if(qt IN_LIST VCPKG_MANIFEST_FEATURES)
    # TODO: do we need "Qt6" ?
    find_package(Qt6 CONFIG REQUIRED)
    find_package(Qt6Core CONFIG REQUIRED)
    find_package(Qt6Widgets CONFIG REQUIRED)
endif()

if(gtkmm IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    pkg_check_modules(GTKMM gtkmm-4.0)
endif()

add_subdirectory(Library)
add_subdirectory(Backends)
add_subdirectory(Examples)
