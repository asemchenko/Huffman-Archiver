cmake_minimum_required(VERSION 3.9)
project(huffmanArchiver)
set(CMAKE_CXX_STANDARD 14)
# enable testing
enable_testing()
# adding tests for SymbolStream
add_subdirectory(SymbolStream/tests)
add_executable(huffmanArchiver main.cpp
        SymbolStream/SymbolStream.cpp SymbolStream/SymbolStream.h
        Symbol/Symbol.h
        API.h API.cpp
        HuffmanTreeNode/HuffmanTreeNode.cpp HuffmanTreeNode/HuffmanTreeNode.h
        HuffmanTree/HuffmanTree.cpp HuffmanTree/HuffmanTree.h)