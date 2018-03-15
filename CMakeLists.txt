cmake_minimum_required(VERSION 3.9)
project(huffmanArchiver)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffmanArchiver main.cpp SymbolInStream/SymbolInStream.cpp SymbolInStream/SymbolInStream.h Symbol/Symbol.h API.h HuffmanTreeNode/HuffmanTreeNode.cpp HuffmanTreeNode/HuffmanTreeNode.h API.cpp HuffmanTree/HuffmanTree.cpp HuffmanTree/HuffmanTree.h)