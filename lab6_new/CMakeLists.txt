cmake_minimum_required(VERSION 3.17)
project(lab6_new C)

set(CMAKE_C_STANDARD 99)

add_executable(lab6 main.c bmp.c bmp.h image.c image.h util.c util.h)