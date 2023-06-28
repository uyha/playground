cmake_minimum_required(VERSION 3.21)
project(Project VERSION 0.1.0 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "/home/uy/scope/build/install/lib/cmake/scope")

find_package(scope REQUIRED)

add_executable(random random.cpp)
target_link_libraries(random PRIVATE scope::scope)
