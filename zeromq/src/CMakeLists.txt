include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(cppzmq REQUIRED)

macro(sandbox_add_executable name)
  add_executable("${name}" "${name}.cpp" ${ARGN})
  target_link_libraries("${name}" PRIVATE fmt::fmt cppzmq::cppzmq)
target_compile_features("${name}" PRIVATE cxx_std_20)
target_compile_options("${name}" PRIVATE ${warnings} ${wae})
endmacro()

add_subdirectory(chapter1)
