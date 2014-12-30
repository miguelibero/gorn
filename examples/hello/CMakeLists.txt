cmake_minimum_required(VERSION 2.8) 

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DGORN_PLATFORM_LINUX")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

project(gorn_hello)

file(GLOB SOURCES "./*.cpp")
add_executable(hello ${SOURCES})
target_link_libraries(hello gorn)
