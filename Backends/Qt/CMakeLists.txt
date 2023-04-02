project(UserInterface.Qt)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Qt6::Core Qt6::Widgets)