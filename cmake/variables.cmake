#!/usr/bin/env -S cmake -P

get_cmake_property(variables VARIABLES)

list(APPEND VARIABLES "${variables}")

message(STATUS "${VARIABLES}")
list(LENGTH variables var_len)
message(STATUS "${var_len}")

list(LENGTH VARIABLES var_len)
message(STATUS "${var_len}")
