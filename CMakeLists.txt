cmake_minimum_required(VERSION 3.12)
project(jsbundler C)

set(CMAKE_C_STANDARD 99)

add_executable(jsbundler main.c file-system.c file-system.h)
