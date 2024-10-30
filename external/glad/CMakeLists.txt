cmake_minimum_required (VERSION 3.8)

project(glad)

add_library(glad STATIC src/gl.c include/glad/gl.h)
target_include_directories(glad PUBLIC include/)