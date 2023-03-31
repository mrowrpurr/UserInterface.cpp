cmake_minimum_required(VERSION 3.21)

project(UserInterface VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

# Include my Logging library for help developing this stuffs...
find_package(spdlog CONFIG REQUIRED)
add_subdirectory("$ENV{LOGGING_LIBRARY}" "${CMAKE_CURRENT_BINARY_DIR}/LoggingLibrary")
message(STATUS "Logging library: $ENV{LOGGING_LIBRARY}")
target_link_libraries(${PROJECT_NAME} INTERFACE Logging spdlog::spdlog)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# include(GNUInstallDirs)

# install(DIRECTORY include DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/..")

# install(
# TARGETS ${PROJECT_NAME}
# EXPORT ${PROJECT_NAME}-targets
# ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# install(
# EXPORT ${PROJECT_NAME}-targets
# FILE ${PROJECT_NAME}-targets.cmake
# NAMESPACE "${PROJECT_NAME}::"
# DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
# )

# configure_file(
# cmake/Config.cmake.in
# ${PROJECT_NAME}Config.cmake
# @ONLY
# )

# install(
# FILES
# "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
# DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
# )
add_subdirectory(Examples)
