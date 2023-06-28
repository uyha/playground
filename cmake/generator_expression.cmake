cmake_minimum_required(VERSION 3.26)
project(project)
set(exp [[$<PATH:HAS_ROOT_NAME,"/a">]])
add_custom_target(print
  COMMAND echo 1 ${exp}
)
