project(userinterface-nana)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE userinterface-interfaces)

find_package(unofficial-nana CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE unofficial::nana::nana)
