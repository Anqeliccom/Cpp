cmake_minimum_required(VERSION 3.14)
project(tasks)

set(CMAKE_CXX_STANDARD 11)

add_executable(segment_tree SegmentTree.cpp SegmentTreeTest.cpp)

option(ENABLE_SANITIZERS "Enable sanitizers for SegmentTree testing" OFF)

# Note: option can be enabled in bash using `cmake -DENABLE_SANITIZERS=ON <build_dir>`
# then rebuild your project `cmake --build <build_dir>` 
# it might be more comfortable then compile code with sanitizers by hands
if(ENABLE_SANITIZERS)
    set(SAN "-fsanitize=address,leak,undefined") 
    target_compile_options(segment_tree PRIVATE ${SAN})
    target_link_options(segment_tree PRIVATE ${SAN})
endif()
