cmake_minimum_required(VERSION 2.8) 

project(gorn_triangle)

add_definitions(-Wall -std=c++11 -Wno-unknown-pragmas)
add_definitions(-DGLM_FORCE_RADIANS)
add_definitions(-DGORN_PLATFORM_LINUX)
add_definitions(-DGORN_DEBUG_PNG_IMAGE_LOADER)

add_subdirectory(../../../proj.linux "${CMAKE_CURRENT_BINARY_DIR}/gorn")

#TODO: find include dirs
include_directories(../../../src)
include_directories(../../../lib)

file(GLOB SOURCES "../*.cpp")
add_executable(triangle ${SOURCES})
target_link_libraries(triangle gorn)
