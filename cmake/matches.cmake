if(gcc MATCHES "^gcc$")
  message(STATUS "Matched")
endif()

if("--std=c++20 -stdlib=libc++ --std" MATCHES [[-stdlib=libc\+\+]])
  message(STATUS "Matched")
endif()
