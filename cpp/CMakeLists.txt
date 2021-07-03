cmake_minimum_required(VERSION 3.18)
project(sandbox LANGUAGES CXX)

macro(add_snippet target)
  add_executable(${target} ${target}.cpp)
endmacro()

add_snippet(compiler_macro)

