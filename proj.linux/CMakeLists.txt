cmake_minimum_required(VERSION 2.8) 

project(gorn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
add_definitions(-DGLM_FORCE_RADIANS)
add_definitions(-DGORN_PLATFORM_LINUX)

# glm
add_subdirectory(../lib/glm "${CMAKE_CURRENT_BINARY_DIR}/glm")

# buffer
add_subdirectory(../lib/buffer "${CMAKE_CURRENT_BINARY_DIR}/buffer")

# library
include_directories(../src)
include_directories(../lib)
include_directories(../lib/buffer/src)
set(GORN_SOURCE_DIR "../src/gorn")
set(GORN_INCLUDE_DIR "../src")

file(GLOB GORN_SOURCES
	"${GORN_SOURCE_DIR}/*.cpp"
	"${GORN_SOURCE_DIR}/asset/*.cpp"
	"${GORN_SOURCE_DIR}/base/*.cpp"
	"${GORN_SOURCE_DIR}/gl/*.cpp"
	"${GORN_SOURCE_DIR}/render/*.cpp"
	"${GORN_SOURCE_DIR}/platform/*.cpp"
	"${GORN_SOURCE_DIR}/platform/linux/*.cpp"
)
add_library(gorn ${GORN_SOURCES})
target_link_libraries(gorn GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi png buffer)
