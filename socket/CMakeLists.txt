cmake_minimum_required(VERSION 3.19)
project(socket)

add_executable(socket main.cpp)
target_compile_features(socket PRIVATE cxx_std_20)
