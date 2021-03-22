cmake_minimum_required(VERSION 3.0)

set(PROJ "opengl")

project(${PROJ})

include_directories(../../../graphics_libraries/${PROJ}/include)
include_directories(../../../interface)

file(
    GLOB
    SRCS
    ../../../graphics_libraries/${PROJ}/src/*.cpp
    ../../../graphics_libraries/${PROJ}/src/*/*.cpp
)
add_library(${PROJ} SHARED ${SRCS})
target_compile_options(${PROJ} PRIVATE -Wall -Wextra)