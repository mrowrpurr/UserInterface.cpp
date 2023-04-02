function(example ExampleName)
    set(target_name Examples.${ExampleName})

    add_executable(${target_name} ${ExampleName}Example.cpp)
    set_target_properties(${target_name} PROPERTIES WIN32_EXECUTABLE TRUE)

    # User Interface core library
    target_link_libraries(${target_name} PRIVATE UserInterface)

    # Logging
    target_link_libraries(${target_name} PRIVATE Logging)

    if(nana IN_LIST VCPKG_MANIFEST_FEATURES)
        # target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nana::nana)
    endif()

    if(fltk IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${target_name} PRIVATE UserInterface.FLTK)
    endif()

    if(wxwidgets IN_LIST VCPKG_MANIFEST_FEATURES)
        target_link_libraries(${target_name} PRIVATE UserInterface.wxWidgets)
    endif()

    if(imgui-glfw3-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
        # target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
        # target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
        # target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    endif()

    if(imgui-sdl2-opengl IN_LIST VCPKG_MANIFEST_FEATURES)
        # target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
        # target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
        # target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static)
        # target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
    endif()

    if(qt IN_LIST VCPKG_MANIFEST_FEATURES)
        find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
        target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Widgets)
        target_link_libraries(${target_name} PRIVATE UserInterface.Qt)
    endif()

    if(gtkmm IN_LIST VCPKG_MANIFEST_FEATURES)
        # target_include_directories(${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
        # target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARIES} ${GTKMM_LIBRARIES})

        # foreach(package gtk gtkmm glib glibmm gettext pcre2 libffi zlib brotli expat freetype pango fribidi harfbuzz cairo cairomm gdk-pixbuf tiff libjpeg-turbo libpng libwebp atk atkmm gdk-pixbufmm glibmm pangomm liblzma graphene libepoxy fontconfig bzip2 pixman libsigcpp)
        # target_link_directories(
        # ${PROJECT_NAME}
        # PRIVATE
        # "$ENV{VCPKG_ROOT}/packages/${package}_x86-dynamic-by-default/lib"
        # "$ENV{VCPKG_ROOT}/packages/${package}_x86-dynamic-by-default/debug/lib"
        # )
        # endforeach()
    endif()
endfunction()

add_subdirectory(Window)

# add_subdirectory(Button)
