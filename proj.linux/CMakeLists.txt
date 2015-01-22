cmake_minimum_required(VERSION 2.8) 

project(gorn)

add_definitions(-Wall -std=c++11 -Wno-unknown-pragmas)
add_definitions(-DGLM_FORCE_RADIANS)
add_definitions(-DGORN_PLATFORM_LINUX)

# glm
add_subdirectory(../lib/glm "${CMAKE_CURRENT_BINARY_DIR}/glm")

# library
include_directories(../src)
include_directories(../lib)
set(GORN_SOURCE_DIR "../src/gorn")
set(GORN_INCLUDE_DIR "../src")

file(GLOB GORN_SOURCES
	"${GORN_SOURCE_DIR}/*.cpp"
	"${GORN_SOURCE_DIR}/asset/*.cpp"
	"${GORN_SOURCE_DIR}/base/*.cpp"
	"${GORN_SOURCE_DIR}/render/*.cpp"
	"${GORN_SOURCE_DIR}/platform/*.cpp"
	"${GORN_SOURCE_DIR}/platform/linux/*.cpp"
)
add_library(gorn ${GORN_SOURCES})
target_link_libraries(gorn GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi png)
