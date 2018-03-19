cmake_minimum_required(VERSION 3.9)
project(huffmanArchiver)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
set(SOURCE_DIR src/)


enable_testing()
add_subdirectory(${SOURCE_DIR}SymbolStream/tests)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("*********************** RELEASE CONFIGURATION ***************************")
    # enable testing
    # adding tests for SymbolStream
    add_compile_options("-O3")
endif ()
add_executable(huffmanArchiver
        ${SOURCE_DIR}main.cpp
        ${SOURCE_DIR}SymbolStream/SymbolStream.cpp
        ${SOURCE_DIR}Symbol/Symbol.cpp
        ${SOURCE_DIR}API.cpp
        ${SOURCE_DIR}HuffmanTreeNode/HuffmanTreeNode.cpp
        ${SOURCE_DIR}HuffmanTree/HuffmanTree.cpp)
