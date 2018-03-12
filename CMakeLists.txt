cmake_minimum_required(VERSION 3.9)
project(huffmansCode C)

set(CMAKE_C_STANDARD 11)

add_executable(huffmansCode main.c huffmanFileProcessor.c huffmanFileProcessor.h)