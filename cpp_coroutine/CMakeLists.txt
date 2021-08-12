cmake_minimum_required(VERSION 3.20)
project(cpp_coroutine)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_20)

