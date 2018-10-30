# cmake_minimum_required(VERSION <specify CMake version here>)
project(targil1 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -Wvla -Wextra -lm")

add_executable(targil1 main.c fileReadTest.c)