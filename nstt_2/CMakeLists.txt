cmake_minimum_required(VERSION 3.29)
project(tasks)

set(CMAKE_CXX_STANDARD 17)

# Note: one of the reasons to not inlude source files can be seen here
# This command build all sources: Lines.cpp LinesTest.cpp
# but code of Lines.cpp is already copy-pasted by preprocessor in LinesTest.cpp
# So the same code compiles twise
# We include Lines.cpp to this list because we need to recompile LinesTest.cpp
# when Lines.cpp is changed
# but headers files in this list won't be compiled, but they will be marked as dependency
add_executable(lines Lines.cpp LinesTest.cpp
        Lines.hpp)
