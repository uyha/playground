include(CompileOptions)
include(Conan)

find_package(cppzmq REQUIRED)
find_package(fmt REQUIRED)

add_library(sandbox_pch INTERFACE)
target_precompile_headers(sandbox_pch INTERFACE <zmq.hpp>)
target_link_libraries(sandbox_pch INTERFACE cppzmq::cppzmq)

macro(sandbox_add_executable name)
  add_executable("${name}" "${name}.cpp" ${ARGN})
  target_link_libraries("${name}" PRIVATE fmt::fmt sandbox_pch)
  target_compile_features("${name}" PRIVATE cxx_std_20)
  target_compile_options("${name}" PRIVATE ${warnings} ${wae})
endmacro()

add_subdirectory(chapter1)
