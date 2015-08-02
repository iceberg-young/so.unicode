cmake_minimum_required(VERSION 3.2)

project(so.utf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES
    mbcs.cpp
    utf8.cpp
    utf16.cpp
    utf32.cpp
    escape.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
include_directories(../include)
