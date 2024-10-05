cmake_minimum_required(VERSION 3.21)
project(template-in-cpp VERSION 0.1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_executable(main main.cpp impl.cpp)


