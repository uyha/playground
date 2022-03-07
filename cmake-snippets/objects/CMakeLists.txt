cmake_minimum_required(VERSION 3.19)
project(objects)

add_library(objects OBJECT main.cpp)

add_custom_target(genexdebug COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_OBJECTS:objects>")
