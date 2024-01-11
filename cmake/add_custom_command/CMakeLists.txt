cmake_minimum_required(VERSION 3.21)
project(Random VERSION 0.1.0 LANGUAGES CXX)

add_executable(main main.cpp)

add_custom_command(OUTPUT dummy
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/script.cmake" "$<TARGET_FILE:main>"
)

add_custom_target(target DEPENDS dummy)
