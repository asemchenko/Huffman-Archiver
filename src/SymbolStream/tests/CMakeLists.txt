cmake_minimum_required(VERSION 3.9)
project(SymbolStreamTests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
add_executable(streamTest tests.cpp ../SymbolStream.cpp ../Symbol.cpp)
target_link_libraries(streamTest ${GTEST_LIBRARIES} Threads::Threads gtest_main)
# copying data for tests
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/uniqBytes.bin"
        "${CMAKE_CURRENT_BINARY_DIR}/uniqBytes.bin"
        COPYONLY)
add_test(streamTest streamTest )
set_tests_properties(streamTest PROPERTIES TIMEOUT 5)