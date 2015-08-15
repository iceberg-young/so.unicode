cmake_minimum_required(VERSION 3.2)

project(so.utf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES
    utf8.cpp
    utf16.cpp
    utf32.cpp
    escape.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
add_library(${PROJECT_NAME}-mbcs STATIC mbcs.cpp)
include_directories(../include)
