cmake_minimum_required(VERSION 3.1.3)

project(hello VERSION 1.0.0 LANGUAGES "C")

set( HELLO_SRCS 
    hello.c
)

option( CROSSCOMPILE_ENABLED "Whether to build for arm" OFF)

if (CROSSCOMPILE_ENABLED)
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR aarch64)
    set(target_arch aarch64-linux-gnu)
    set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)
    set(CMAKE_LIBRARY_ARCHITECTURE ${target_arch} CACHE STRING "" FORCE)
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif()

add_executable(${PROJECT_NAME} ${HELLO_SRCS})