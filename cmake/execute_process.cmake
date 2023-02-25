execute_process(
  COMMAND conan -fd
  COMMAND_ERROR_IS_FAT LAST
)

message(STATUS "${result}")
