cmake_minimum_required(VERSION 3.16)
project(megazip)

set(CMAKE_CXX_STANDARD 20)

add_executable(megazip main.cpp string_table.cpp string_table.h packer.cpp packer.h unpacker.cpp unpacker.h code_output_stream.cpp code_output_stream.h)