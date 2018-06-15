cmake_minimum_required(VERSION 3.10)
project(copyconst)

set(CMAKE_CXX_STANDARD 11)

add_executable(copyconst main.cpp Node.cpp Node.h Board.cpp Board.h)