cmake_minimum_required(VERSION 3.20)
project(BinaryTreePrinter C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(BinaryTreePrinter main.c src/BtPrinter.c)
