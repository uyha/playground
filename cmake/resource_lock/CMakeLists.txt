cmake_minimum_required(VERSION 3.16)
project(ResourceLockDemo VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

add_executable(main test.cpp)

add_test(test1 main)
set_tests_properties(test1 PROPERTIES RESOURCE_LOCK resource)

add_test(test2 main)
set_tests_properties(test2 PROPERTIES RESOURCE_LOCK resource)
