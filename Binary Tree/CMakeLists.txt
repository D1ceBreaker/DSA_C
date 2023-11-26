cmake_minimum_required(VERSION 3.25)
project(bin_tree_strings C)

set(CMAKE_C_STANDARD 99)

add_executable(bin_tree_strings timing.c tree.c tree.h user.c user.h )
