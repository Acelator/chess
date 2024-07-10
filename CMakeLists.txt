cmake_minimum_required(VERSION 3.25)

project(learning
        VERSION 0.1.0
        DESCRIPTION ""
        LANGUAGES CXX
)

#add_library(engine SHARED "lib/engine/**/*.cpp" "lib/engine/**/*.h")
#set_target_properties(engine PROPERTIES VERSION ${PROJECT_VERSION})

#Config
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


file(GLOB SOURCES "src/*.cpp" "src/*.h" "src/**/*.cpp" "src/**/*.h")

add_executable(main ${SOURCES})
target_compile_options(main PUBLIC -Wall -Wfloat-conversion)
