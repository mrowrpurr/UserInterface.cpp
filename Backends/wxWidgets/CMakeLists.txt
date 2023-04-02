project(UserInterface.wxWidgets)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

# Logging
target_link_libraries(${PROJECT_NAME} INTERFACE Logging)

# wxWidgets
find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE wx::core wx::base)
