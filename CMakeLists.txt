cmake_minimum_required(VERSION 3.17)
project(megazip)

set(CMAKE_CXX_STANDARD 20)

add_executable(megazip main.cpp string_table.cpp string_table.h compressor.h compressor.cpp)