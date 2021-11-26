cmake_minimum_required(VERSION 3.18)
project(sandbox LANGUAGES CXX)

macro(add_snippet target)
  add_executable(${target} ${target}.cpp)
  target_compile_features(${target} PRIVATE cxx_std_20)
endmacro()

add_snippet(compiler_macro)
add_snippet(chrono_duration)

