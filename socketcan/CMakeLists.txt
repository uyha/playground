cmake_minimum_required(VERSION 3.19)
project(socketcan)

add_executable(socketcan main.cpp)
target_compile_features(socketcan PRIVATE cxx_std_20)
