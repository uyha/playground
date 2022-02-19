cmake_minimum_required(VERSION 3.21)
project(gcov)


add_library(gcov INTERFACE)
target_compile_options(gcov INTERFACE --coverage)
target_link_options(gcov INTERFACE --coverage)

add_executable(main main.cpp lib.cpp)
target_link_libraries(main PRIVATE gcov)
