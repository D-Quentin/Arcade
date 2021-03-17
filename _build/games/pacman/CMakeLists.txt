cmake_minimum_required(VERSION 3.0)

set(PROJ "pacman")

project(${PROJ})

include_directories(../../../games/${PROJ}/include)

file(
    GLOB
    SRCS
    ../../../games/${PROJ}/src/*.cpp
    ../../../games/${PROJ}/src/*/*.cpp
)
add_library(${PROJ} SHARED ${SRCS})
target_compile_options(${PROJ} PRIVATE -Wall -Wextra)