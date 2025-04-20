cmake_minimum_required(VERSION 3.29)
project(tasks)

set(CMAKE_CXX_STANDARD 17)

add_executable( prime isPrime.hpp
        isPrime.cpp
)