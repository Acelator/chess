cmake_minimum_required(VERSION 3.25)

project(learning
        VERSION 0.1.0
        DESCRIPTION ""
        LANGUAGES CXX
)

#Config
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


file(GLOB SOURCES "src/*.cpp" "src/*.h" "src/**/*.cpp" "src/**/*.h")

add_executable(main ${SOURCES})
target_compile_options(main PUBLIC -Wall -Wfloat-conversion)
