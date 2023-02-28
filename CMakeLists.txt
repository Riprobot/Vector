cmake_minimum_required(VERSION 3.22)
project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(Vector tests/test.cpp vector.cpp tests/catch/catch_main.cpp)
