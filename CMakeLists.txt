cmake_minimum_required(VERSION 3.9)
project(huffmanArchiver)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")
set(SOURCE_DIR src/)


enable_testing()
add_subdirectory(${SOURCE_DIR}SymbolStream/tests)
add_subdirectory(${SOURCE_DIR}HuffmanTree/tests)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("*********************** RELEASE CONFIGURATION ***************************")
    # enable testing
    # adding tests for SymbolStream
    add_compile_options("-O3")
endif ()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("*********************** DEBUG CONFIGURATION ***************************")
    add_definitions(-DDEBUG)
endif ()
add_executable(huffmanArchiver
        ${SOURCE_DIR}main.cpp
        ${SOURCE_DIR}SymbolStream/SymbolStream.cpp
        ${SOURCE_DIR}SymbolStream/Symbol.cpp
        ${SOURCE_DIR}API.cpp
        ${SOURCE_DIR}HuffmanTree/Node.cpp
        ${SOURCE_DIR}HuffmanTree/HuffmanTree.cpp)
