cmake_minimum_required(VERSION 2.8) 

project(gorn_triangle)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-Wall -std=c++11 -Wno-unknown-pragmas)
add_definitions(-DGLM_FORCE_RADIANS)
add_definitions(-DGORN_PLATFORM_LINUX)
add_definitions(-DGORN_DEBUG_PNG_IMAGE_LOADER)

add_subdirectory(../../../proj.linux "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/gorn")

#TODO: find include dirs
include_directories(../../../src)
include_directories(../../../lib)

file(GLOB SOURCES "../src/*.cpp")
add_executable(triangle ${SOURCES})
target_link_libraries(triangle gorn)
