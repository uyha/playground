cmake_minimum_required(VERSION 3.18)
project(sandbox LANGUAGES CXX)

macro(add_snippet target)
  add_executable(${target} ${target}.cpp)
  target_compile_features(${target} PRIVATE cxx_std_20)
endmacro()

add_snippet(compiler_macro)
add_snippet(sml)
add_snippet(template_template)
add_snippet(member_variable_capture_by_ref)
add_snippet(anonymous_struct)
add_snippet(chrono_duration)
