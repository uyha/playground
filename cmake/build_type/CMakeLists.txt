cmake_minimum_required(VERSION 3.21)
project(build_type)

add_executable(main main.cpp)

message(STATUS "${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "${CMAKE_LDFLAGS}")
