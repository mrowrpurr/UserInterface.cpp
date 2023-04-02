project(UserInterface VERSION 0.1.0)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE Logging)
target_include_directories(${PROJECT_NAME} INTERFACE include)
