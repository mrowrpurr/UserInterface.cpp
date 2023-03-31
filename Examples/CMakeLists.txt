# Find packages for the selected GUI library
if(VCPKG_MANIFEST_FEATURES STREQUAL nana)
    find_package(unofficial-nana CONFIG REQUIRED)

elseif(VCPKG_MANIFEST_FEATURES STREQUAL fltk)
    find_package(FLTK CONFIG REQUIRED)

elseif(VCPKG_MANIFEST_FEATURES STREQUAL wxwidgets)
    find_package(wxWidgets CONFIG REQUIRED)

elseif(VCPKG_MANIFEST_FEATURES STREQUAL qt)
    # TODO: do we need "Qt6" ?
    find_package(Qt6 CONFIG REQUIRED)
    find_package(Qt6Core CONFIG REQUIRED)
    find_package(Qt6Widgets CONFIG REQUIRED)

elseif(VCPKG_MANIFEST_FEATURES STREQUAL imgui)
    find_package(imgui CONFIG REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)

elseif(VCPKG_MANIFEST_FEATURES STREQUAL gtkmm)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    pkg_check_modules(GTKMM gtkmm-4.0)

else()
    message(FATAL_ERROR "No GUI library selected")
endif()

function(link_current_gui_library ExampleProjectName)
    if(VCPKG_MANIFEST_FEATURES STREQUAL nana)
        target_link_libraries(${ExampleProjectName} PRIVATE unofficial::nana::nana)

    elseif(VCPKG_MANIFEST_FEATURES STREQUAL fltk)
        target_link_libraries(${ExampleProjectName} PRIVATE fltk fltk_gl fltk_forms)

    elseif(VCPKG_MANIFEST_FEATURES STREQUAL wxwidgets)
        target_link_libraries(${ExampleProjectName} PRIVATE wx::core wx::base)

        target_link_libraries(${ExampleProjectName} PRIVATE Qt::Core Qt::Widgets)
    elseif(VCPKG_MANIFEST_FEATURES STREQUAL qt)
    elseif(VCPKG_MANIFEST_FEATURES STREQUAL imgui)
        target_link_libraries(${ExampleProjectName} PRIVATE imgui::imgui)
        target_link_libraries(${ExampleProjectName} PRIVATE glfw)
        target_link_libraries(${ExampleProjectName} PRIVATE OpenGL::GL)

    elseif(VCPKG_MANIFEST_FEATURES STREQUAL gtkmm)
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

    else()
        message(FATAL_ERROR "No GUI library selected")
    endif()
endfunction()

function(create_sample)
endfunction()

function(sample SampleName)
    add_executable(Examples.${SampleName} ${SampleName}Example.cpp)
    set_target_properties(Examples.${SampleName} PROPERTIES WIN32_EXECUTABLE TRUE)
    link_current_gui_library(Examples.${SampleName})
endfunction()

add_subdirectory(Window)
