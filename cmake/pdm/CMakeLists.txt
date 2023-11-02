cmake_minimum_required(VERSION 3.21)
project(pdm)

list(PREPEND CMAKE_MODULE_PATH "/home/uy/Personal/cmake-modules")

add_subdirectory(sub)
include(Pdm)

find_package(Python REQUIRED)
