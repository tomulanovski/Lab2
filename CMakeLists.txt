cmake_minimum_required(VERSION 3.23)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled1 myshell.c LineParser.c LineParser.h Looper.c)
