cmake_minimum_required(VERSION 3.18)
project(fetch_content)

include(ExternalProject)
set(neobot_src ${CMAKE_BINARY_DIR}/_deps/neobot_src)
set(neobot_build ${CMAKE_BINARY_DIR}/_deps/neobot_build)
ExternalProject_Add(neobot
  GIT_REPOSITORY git@github.com:kewazo/neobot.git
  SOURCE_DIR ${neobot_src}
  BINARY_DIR ${neobot_build}
  CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${neobot_src}/tools/toolchains/arm.cmake
             -DCMAKE_FIND_ROOT_PATH=/home/uy/Work/image/build/dev-rootfs
             -DCMAKE_SYSROOT=/home/uy/Work/image/build/dev-rootfs
  STEP_TARGETS configure
)
