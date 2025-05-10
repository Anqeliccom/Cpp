cmake_minimum_required(VERSION 3.29)
project(tasks)

set(CMAKE_CXX_STANDARD 20)

add_executable( smart_ptr SegmentTree.hpp
        SegmentTreeTest.cpp
)