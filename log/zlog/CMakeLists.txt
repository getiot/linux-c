cmake_minimum_required(VERSION 3.0)

project(zlog LANGUAGES C)

find_library(ZLOG_LIBRARY NAMES zlog)
message(STATUS "${ZLOG_LIBRARY}")

link_directories("/usr/local/lib")
include_directories("/usr/local/include")

add_executable(zlog_example zlog_example.c)
add_executable(dzlog_example dzlog_example.c)

target_link_libraries(zlog_example PUBLIC zlog)
target_link_libraries(dzlog_example PUBLIC zlog)