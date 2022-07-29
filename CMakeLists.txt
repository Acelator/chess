cmake_minimum_required(VERSION 3.20)
project(chess VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(EXEC chess)

# Flags
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")

# Default build type
#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release)
#endif()

# Files
include_directories(src)
file(GLOB SOURCES src/*.cpp)
file(GLOB MOVE src/movement/**.cpp)
file(GLOB UTILS src/utils/*.cpp)

add_executable(${EXEC} ${SOURCES} ${MOVE} ${UTILS})
