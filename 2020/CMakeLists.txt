cmake_minimum_required(VERSION 3.1)
project(2020)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "--coverage")

add_executable(2020 main.cpp)