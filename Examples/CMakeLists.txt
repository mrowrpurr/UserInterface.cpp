if(nana IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(unofficial-nana CONFIG REQUIRED)
endif()

if(fltk IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(FLTK CONFIG REQUIRED)
endif()

if(wxwidgets IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(wxWidgets CONFIG REQUIRED)
endif()

# TODO: add another feature for ImGUI SDL2 backend to test both backends
if(imgui-glfw3-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(imgui CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
endif()

if(imgui-sdl2-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
    find_package(imgui CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(SDL2 CONFIG REQUIRED)

    # message(STATUS "INCLUDE DIRS ${SDL2_INCLUDE_DIRS}")
    # message(STATUS "LIBRARIES: ${SDL2_LIBRARIES}")
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

function(link_current_gui_libraries ExampleProjectName)
    if(nana IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${ExampleProjectName} PRIVATE unofficial::nana::nana)
    endif()

    if(fltk IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${ExampleProjectName} PRIVATE fltk fltk_gl fltk_forms)
    endif()

    if(wxwidgets IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${ExampleProjectName} PRIVATE wx::core wx::base)
    endif()

    if(imgui-glfw3-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${ExampleProjectName} PRIVATE imgui::imgui)
        target_link_libraries(${ExampleProjectName} PRIVATE OpenGL::GL)
        target_link_libraries(${ExampleProjectName} PRIVATE glfw)
    endif()

    if(imgui-sdl2-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${ExampleProjectName} PRIVATE imgui::imgui)
        target_link_libraries(${ExampleProjectName} PRIVATE OpenGL::GL)
        message(STATUS "I AM HERE")
        target_link_libraries(${ExampleProjectName} PRIVATE SDL2::SDL2-static)
        target_link_libraries(${ExampleProjectName} PRIVATE GLEW::GLEW)
        target_include_directories(${ExampleProjectName} PRIVATE ${SDL2_INCLUDE_DIRS})
        target_link_directories(
            ${ExampleProjectName}
            PRIVATE
            "$ENV{VCPKG_ROOT}/packages/sdl2_x86-windows-static-md/lib"
        )
    endif()

    if(qt IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${ExampleProjectName} PRIVATE Qt::Core Qt::Widgets)
    endif()

    if(gtkmm IN_LIST VCPKG_MANIFEST_FEATURES)
        target_include_directories(${ExampleProjectName} PRIVATE ${GTK4_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
        target_link_libraries(${ExampleProjectName} PRIVATE ${GTK4_LIBRARIES} ${GTKMM_LIBRARIES})

        foreach(package gtk gtkmm glib glibmm gettext pcre2 libffi zlib brotli expat freetype pango fribidi harfbuzz cairo cairomm gdk-pixbuf tiff libjpeg-turbo libpng libwebp atk atkmm gdk-pixbufmm glibmm pangomm liblzma graphene libepoxy fontconfig bzip2 pixman libsigcpp)
            target_link_directories(
                ${ExampleProjectName}
                PRIVATE
                "$ENV{VCPKG_ROOT}/packages/${package}_x86-dynamic-by-default/lib"
                "$ENV{VCPKG_ROOT}/packages/${package}_x86-dynamic-by-default/debug/lib"
            )
        endforeach()
    endif()
endfunction()

function(sample SampleName)
    add_executable(Examples.${SampleName} ${SampleName}Example.cpp)
    set_target_properties(Examples.${SampleName} PROPERTIES WIN32_EXECUTABLE TRUE)
    link_current_gui_libraries(Examples.${SampleName})
    target_link_libraries(Examples.${SampleName} PRIVATE UserInterface Logging)
endfunction()

add_subdirectory(Window)
add_subdirectory(Button)
