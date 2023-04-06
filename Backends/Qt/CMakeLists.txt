project(userinterface-qt)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE userinterface-interfaces)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Qt6::Core Qt6::Widgets)