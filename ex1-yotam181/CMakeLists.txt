cmake_minimum_required(VERSION 3.16)

project(EX1 C)

set(CMAKE_C_STANDARD 99)

add_executable(EX1 main.c cipher.c tests.c cipher.h tests.h)
