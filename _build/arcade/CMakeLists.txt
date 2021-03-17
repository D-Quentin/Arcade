cmake_minimum_required(VERSION 3.0)

set(PROJ "arcade")

project(${PROJ})

include_directories(../../arcade_core/include)

file(
    GLOB
    SRCS
    ../../arcade_core/src/*.cpp
    ../../arcade_core/src/*/*.cpp
)
add_executable(${PROJ} ${SRCS})
target_compile_options(${PROJ} PRIVATE -Wall -Wextra)