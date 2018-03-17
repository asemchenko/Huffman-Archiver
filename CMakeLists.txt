cmake_minimum_required(VERSION 3.9)
project(huffmanArchiver)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("*********************** RELEASE CONFIGURATION ***************************")
    # enable testing
    enable_testing()
    # adding tests for SymbolStream
    add_subdirectory(SymbolStream/tests)
    add_compile_options("-O3")
endif ()
add_executable(huffmanArchiver main.cpp
        SymbolStream/SymbolStream.cpp SymbolStream/SymbolStream.h
        Symbol/Symbol.h Symbol/Symbol.cpp
        API.h API.cpp
        HuffmanTreeNode/HuffmanTreeNode.cpp HuffmanTreeNode/HuffmanTreeNode.h
        HuffmanTree/HuffmanTree.cpp HuffmanTree/HuffmanTree.h)
