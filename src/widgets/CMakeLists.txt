cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(PROJECT_NAME bnp.widgets)

set(CMAKE_AUTOMOC ON)

project(${PROJECT_NAME})

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_library(${PROJECT_NAME} STATIC
    MainWindow.cpp
    MainWindow.h
    widgets.cpp
    widgets.h
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets qcustomplot bnp.math)
