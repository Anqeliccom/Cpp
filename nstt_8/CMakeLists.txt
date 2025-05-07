cmake_minimum_required(VERSION 3.29)
project(tasks)

set(CMAKE_CXX_STANDARD 11)

add_executable( readerWriter IO.hpp
        Reader.hpp
        Writer.hpp
        ReaderWriter.hpp
        Tests.cpp
        String/ReaderString.hpp
        String/RW_String.hpp
        String/WriterString.hpp
        File/WriterFile.hpp
        File/ReaderFile.hpp
        File/RW_File.hpp
)