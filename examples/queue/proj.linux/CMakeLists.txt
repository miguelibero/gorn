cmake_minimum_required(VERSION 2.8) 

project(gorn_queue)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-Wall -std=c++11 -Wno-unknown-pragmas)
add_definitions(-DGLM_FORCE_RADIANS)
add_definitions(-DGORN_PLATFORM_LINUX)

add_subdirectory(../../../proj.linux "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/gorn")

#TODO: find include dirs
include_directories(../../../src)
include_directories(../../../lib)

file(GLOB SOURCES "../*.cpp")
add_executable(queue ${SOURCES})
target_link_libraries(queue gorn)
