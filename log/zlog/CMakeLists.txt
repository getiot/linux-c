cmake_minimum_required(VERSION 3.0)

project(zlog LANGUAGES C)

include_directories("/usr/local/include")
find_library(ZLOG_LIBRARY NAMES zlog)
message(STATUS "${ZLOG_LIBRARY}")
link_directories("/usr/local/lib")

set(ZLOG_LIBRARIES ${ZLOG_LIBRARY})
set(ZLOG_INCLUDE_DIRS "/usr/local/include")

#set_target_properties(zlog::zlog PROPERTIES 
#            INTERFACE_INCLUDE_DIRECTORIES "${ZLOG_INCLUDE_DIRS}" 
#            IMPORTED_LINK_INTERFACE_LANGUAGES "C" 
#            IMPORTED_LOCATION "${ZLOG_LIBRARIES}")

add_executable(zlog_example zlog_example.c)
add_executable(dzlog_example dzlog_example.c)

target_link_libraries(zlog_example PUBLIC zlog)
target_link_libraries(dzlog_example PUBLIC zlog)