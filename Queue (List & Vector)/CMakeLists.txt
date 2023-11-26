cmake_minimum_required(VERSION 3.24)
project(RoundRobin C)

set(CMAKE_C_STANDARD 99)

add_executable(RoundRobin main.c input.c queue.c)
