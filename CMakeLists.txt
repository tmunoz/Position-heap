cmake_minimum_required(VERSION 3.7)
project(Research)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        childtable.cpp
        childtable.h
        heap.cpp
        heap.h
        main.cpp
        node.cpp
        node.h)

add_executable(Research ${SOURCE_FILES})