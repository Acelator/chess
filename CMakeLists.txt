cmake_minimum_required(VERSION 3.20)
project(chess VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(EXEC chess)

# Compiler options
set(CMAKE_CXX_FLAGS "-Wall -Werror")

# Files
include_directories(src)
file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})
