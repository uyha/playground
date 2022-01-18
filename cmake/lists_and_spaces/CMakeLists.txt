cmake_minimum_required(VERSION 3.21)
project(sth LANGUAGES NONE)

set(files "etc/ab" etc/c)

add_custom_command(
  OUTPUT ${files}
  COMMAND "${CMAKE_COMMAND}" -E copy_directory etc "${CMAKE_BINARY_DIR}/etc"
  DEPENDS ${files}
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  )
add_custom_target(
  dummy
  DEPENDS ${files}
  )

