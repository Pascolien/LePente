cmake_minimum_required(VERSION 3.3)
project(LePente)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c test.c test.h main.h)
add_executable(LePente ${SOURCE_FILES})