cmake_minimum_required(VERSION 2.8.4)

project(so.unicode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
    utf8.cpp
    utf16.cpp
    utf32.cpp
    wild.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
include_directories(../include)
