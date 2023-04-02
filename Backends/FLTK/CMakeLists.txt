project(UserInterface.FLTK)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

# Logging
target_link_libraries(${PROJECT_NAME} INTERFACE Logging)

# FLTK
find_package(FLTK CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE fltk fltk_gl fltk_forms)
