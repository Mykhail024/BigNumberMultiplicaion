cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(PROJECT_NAME bnp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

project(${PROJECT_NAME})

add_subdirectory(external/qcustomplot)

add_subdirectory(src/math)
add_subdirectory(src/widgets)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} bnp.widgets)
