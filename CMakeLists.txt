cmake_minimum_required(VERSION 3.24)
project(TheVixEngineExamples LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use vcpkg toolchain
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_TOOLCHAIN_FILE}")

# Find packages via vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Sources
set(SOURCES
    TheVixEngine/thevixengine.cpp
    Examples/application/main.cpp
)

# Executable
add_executable(TheVixEngineApp ${SOURCES})

# Link libraries
target_include_directories(TheVixEngineApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/TheVixEngine
)