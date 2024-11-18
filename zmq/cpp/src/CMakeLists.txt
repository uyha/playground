include(CompileOptions)

find_package(fmt REQUIRED)
find_package(cppzmq REQUIRED)

macro(snippet name)
  add_executable(${name} "${name}.cpp")
  target_link_libraries(${name} PRIVATE fmt::fmt cppzmq)
  target_compile_features(${name} PRIVATE cxx_std_20)
  target_compile_options(${name} PRIVATE ${warnings} ${wae})
endmacro()

snippet(req-rep)
snippet(push-pull)
snippet(barebone)
snippet(liveness-check)
