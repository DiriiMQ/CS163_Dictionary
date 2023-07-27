cmake_minimum_required(VERSION 3.26)
project(CS163_Group9)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/source)

add_executable(CS163_Group9 main.cpp
        source/Window.cpp
        source/Window.h
        source/stuff/Constants.h
        source/draw/MainMenu.cpp
        source/draw/MainMenu.h
        source/core/Api.cpp
        source/core/Api.h
)
