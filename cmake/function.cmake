macro(_conan_add_flag option flag)
  message(STATUS ${arg_${option}})
  if(arg_${option})
    list(APPEND args ${flag})
  endif()
endmacro()

macro(_conan_add_values option)
  if(arg_${option})
    foreach(var IN LISTS arg_${option})
      message(STATUS "Here ${var}")
      list(APPEND args "\"${var}\"")
    endforeach()
  endif()
endmacro()

function(scope_fun)
  cmake_parse_arguments(arg "NO_REMOTE" "" "REMOTE" ${ARGN})

  message(STATUS ${arg_REMOTE})
  # _conan_add_flag(NO_REMOTE --no-remote)
  _conan_add_values(REMOTE ${arg_REMOTE})

  execute_process(COMMAND echo ${args})
endfunction()

scope_fun(
  NO_REMOTE
  REMOTE "a b"
  REMOTE b
)
