cmake_minimum_required(VERSION 2.8) 

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DGORN_PLATFORM_LINUX -DGORN_DEBUG_PNG_IMAGE_LOADER")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

project(gorn_hello)

add_subdirectory(../../../proj.linux "${CMAKE_CURRENT_BINARY_DIR}/gorn")

#TODO: find include dirs
include_directories(../../../src)
include_directories(../../../lib)

file(GLOB SOURCES "../*.cpp")
add_executable(hello ${SOURCES})
target_link_libraries(hello gorn)
