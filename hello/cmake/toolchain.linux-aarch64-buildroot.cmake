set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(target_arch aarch64-linux-gnu)
set(CMAKE_C_COMPILER aarch64-buildroot-linux-gnu-gcc)
#set(CMAKE_CXX_COMPILER aarch64-buildroot-linux-gnu-g++)
set(CMAKE_LIBRARY_ARCHITECTURE ${target_arch} CACHE STRING "" FORCE)
set(CMAKE_FIND_ROOT_PATH /opt/buildroot/host/aarch64-buildroot-linux-gnu/sysroot)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)