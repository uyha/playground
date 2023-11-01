cmake_minimum_required(VERSION 3.21)
project(pdm)

list(PREPEND CMAKE_MODULE_PATH "/home/uy/Personal/cmake-modules")

include(/home/uy/Personal/cmake-modules/Pdm.cmake)
message(STATUS "${Pdm_EXECUTABLE}:${Pdm_VERSION}")

