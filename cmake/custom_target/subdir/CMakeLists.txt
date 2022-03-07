add_custom_command(OUTPUT output
  COMMAND ${CMAKE_COMMAND} -E touch output
  )
add_custom_target(gen-output DEPENDS output)
