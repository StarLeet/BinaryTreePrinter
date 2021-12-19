cmake_minimum_required(VERSION 3.20)
project(BinaryTreePrinter)

include_directories(include)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
    )

set(CMAKE_EXPORT_COMPILECOMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(BinaryTreePrinter main.c src/BtPrinter.c)
