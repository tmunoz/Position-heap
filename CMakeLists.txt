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
        node.h fast_stack.hpp)

add_executable(Research ${SOURCE_FILES} fast_stack.hpp)