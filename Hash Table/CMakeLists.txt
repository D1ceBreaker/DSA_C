cmake_minimum_required(VERSION 3.24)
project(lab3c C)

set(CMAKE_C_STANDARD 99)

add_executable(lab3c main.c table.c table.h user.c user.h dialog.c dialog.h)
