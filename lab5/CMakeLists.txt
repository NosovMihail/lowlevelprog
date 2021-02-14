cmake_minimum_required(VERSION 3.17)
project(lab5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(lab5
        io.c
        io.h
        list.c
        list.h
        main.c
        maybe_int.c
        maybe_int.h
        list_io.h list_io.c)
