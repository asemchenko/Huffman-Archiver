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
add_compile_options("-pg")
set(SOURCE_DIR src/)
add_executable(huffmanArchiver ${SOURCE_DIR}main.cpp
        ${SOURCE_DIR}SymbolStream/SymbolStream.cpp
        ${SOURCE_DIR}Symbol/Symbol.cpp
        ${SOURCE_DIR}API.cpp
        ${SOURCE_DIR}HuffmanTreeNode/HuffmanTreeNode.cpp
        ${SOURCE_DIR}HuffmanTree/HuffmanTree.cpp)
