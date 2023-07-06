function(a)
  cmake_parse_arguments(arg ";" ";" "MULTI;" ${ARGN})
  message(STATUS "${arg_MULTI}")
endfunction()

a(
  MULTI 1 2 3 4 5
  MULTI 1
  MULTI 1
  MULTI 1
)
