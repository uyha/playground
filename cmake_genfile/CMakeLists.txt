cmake_minimum_required(VERSION 3.21)
project(cmake_buildtime)

add_executable(gen gen.c)

add_custom_command(OUTPUT header/header.hpp
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/header
  COMMAND gen ${CMAKE_CURRENT_BINARY_DIR}/header/header.hpp
  DEPENDS gen
  )

add_executable(main main.cpp ${CMAKE_CURRENT_BINARY_DIR}/header/header.hpp)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/header)
