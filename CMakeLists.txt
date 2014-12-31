cmake_minimum_required(VERSION 2.8) 

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DGORN_PLATFORM_LINUX -DGORN_DEBUG_PNG_IMAGE_LOADER")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

project(gorn)

# library
include_directories(src)
include_directories(lib)
set(GORN_SOURCE_DIR "src/gorn")

file(GLOB GORN_SOURCES
	"${GORN_SOURCE_DIR}/*.cpp"
	"${GORN_SOURCE_DIR}/base/*.cpp"
	"${GORN_SOURCE_DIR}/render/*.cpp"
	"${GORN_SOURCE_DIR}/platform/*.cpp"
	"${GORN_SOURCE_DIR}/platform/linux/*.cpp"
)
add_library(gorn ${GORN_SOURCES})
target_link_libraries(gorn GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi png)

# examples
include_directories(examples)

# examples: hello
set(GORN_EXAMPLE_HELLO_SOURCE_DIR "examples/hello")
file(GLOB GORN_EXAMPLE_HELLO_SOURCES
	"${GORN_EXAMPLE_HELLO_SOURCE_DIR}/*.cpp"
)
add_executable(hello ${GORN_EXAMPLE_HELLO_SOURCES} ${GORN_EXAMPLE_HELLO_PLATFORM_SOURCES})

target_link_libraries(hello gorn)
