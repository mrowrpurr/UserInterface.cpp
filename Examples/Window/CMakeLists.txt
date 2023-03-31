project(Examples.Window)

# add_subdirectory("$ENV{GLFW_PATH}" "${CMAKE_CURRENT_BINARY_DIR}/glfw")

# find_package(FLTK CONFIG REQUIRED)
# find_package(wxWidgets CONFIG REQUIRED)
# find_package(imgui CONFIG REQUIRED)
# find_package(OpenGL REQUIRED)
# find_package(glfw3 CONFIG REQUIRED)
# find_package(unofficial-nana CONFIG REQUIRED)
# find_package(Qt6 CONFIG REQUIRED)
# find_package(Qt6Core CONFIG REQUIRED)
# find_package(Qt6Widgets CONFIG REQUIRED)
add_executable(${PROJECT_NAME} WindowExample.cpp)

# set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

# target_link_libraries(${PROJECT_NAME} PRIVATE fltk fltk_gl fltk_forms)
# target_link_libraries(${PROJECT_NAME} PRIVATE wx::core wx::base)
# target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
# target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
# target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nana::nana)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GTKMM gtkmm-4.0)

target_include_directories(${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARIES} ${GTKMM_LIBRARIES})

foreach(package gtk gtkmm glib glibmm gettext pcre2 libffi zlib brotli expat freetype pango fribidi harfbuzz cairo cairomm gdk-pixbuf tiff libjpeg-turbo libpng libwebp atk atkmm gdk-pixbufmm glibmm pangomm liblzma graphene libepoxy fontconfig bzip2 pixman libsigcpp)
    target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
        "$ENV{VCPKG_ROOT}/packages/${package}_x86-dynamic-by-default/lib"
        "$ENV{VCPKG_ROOT}/packages/${package}_x86-dynamic-by-default/debug/lib"
    )
endforeach()
