cmake_minimum_required(VERSION 3.29)
project(tasks)

set(CMAKE_CXX_STANDARD 11)

add_executable( scoped_pointer ScopedPointer.hpp
        ScopedPointerTest.cpp
)
