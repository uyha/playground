cmake_minimum_required(VERSION 3.21)
project(ProjectName VERSION 0.1.0 LANGUAGES CXX)

add_custom_target(A)

set_target_properties(A
  PROPERTIES
    timeout 1
    timeout 12
)

get_target_property(timeout A timeout)
message(STATUS ${timeout})
