cmake_minimum_required (VERSION 2.8)
project (BashShell)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -D_XOPEN_SOURCE=500 -Wall")

include_directories(${CMAKE_CURRENT_DIRECTORY}/include/test.h)

add_executable (bashShell src/commands/test.c)