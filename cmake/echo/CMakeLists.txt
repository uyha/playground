cmake_minimum_required(VERSION 3.18)
project(echo)

message(STATUS "CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "SOME_VAR: $CACHE{SOME_VAR}")
