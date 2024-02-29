cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(PROJECT_NAME bnp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

project(${PROJECT_NAME})

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)
