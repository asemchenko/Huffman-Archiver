cmake_minimum_required(VERSION 3.9)
project(SymbolStreamTests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
add_executable(streamTest tests.cpp)
target_link_libraries(streamTest ${GTEST_LIBRARIES} Threads::Threads gtest_main)