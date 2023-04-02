cmake_minimum_required(VERSION 3.21)

project(UserInterface-Project LANGUAGES CXX)

# Logging library [at least temporarily...]
add_subdirectory("$ENV{LOGGING_LIBRARY}" "${CMAKE_CURRENT_BINARY_DIR}/LoggingLibrary")

add_subdirectory(Library)
add_subdirectory(Backends)
add_subdirectory(Examples)
