project(Examples.Window)

# find_package(FLTK CONFIG REQUIRED)
# find_package(wxWidgets CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# find_package(GLEW REQUIRED)
find_package(gl3w CONFIG REQUIRED)

# find_package(unofficial-nana CONFIG REQUIRED)
add_executable(${PROJECT_NAME} WindowExample.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

# target_link_libraries(${PROJECT_NAME} PRIVATE fltk fltk_gl fltk_forms)
# target_link_libraries(${PROJECT_NAME} PRIVATE wx::core wx::base)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::gl3w::gl3w)

# target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nana::nana)
