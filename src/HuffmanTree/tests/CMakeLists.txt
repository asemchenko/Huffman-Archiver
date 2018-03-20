cmake_minimum_required(VERSION 3.9)
project(HuffmanTreeTests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
add_executable(huffmanTreeTest tests.cpp
        ../HuffmanTree.cpp
        ../../Symbol/Symbol.cpp
        ../../HuffmanTreeNode/HuffmanTreeNode.cpp
        ../../SymbolStream/SymbolStream.cpp)
target_link_libraries(huffmanTreeTest ${GTEST_LIBRARIES} Threads::Threads gtest_main)
# copying data for tests
add_test(huffmanTreeTest huffmanTreeTest )
set_tests_properties(huffmanTreeTest PROPERTIES TIMEOUT 5)