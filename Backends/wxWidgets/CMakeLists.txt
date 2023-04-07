project(userinterface-wxwidgets)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE userinterface-interfaces)

# wxWidgets
find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE wx::core wx::base)
