cmake_minimum_required(VERSION 3.12)
project(something)

include(FetchContent)
FetchContent_Declare(river
                     GIT_REPOSITORY https://github.com/uyha/cmake-modules.git
                     GIT_TAG v0.2.0
                     PATCH_COMMAND git apply ${PROJECT_SOURCE_DIR}/ccache.patch
)
FetchContent_MakeAvailable(river)
list(APPEND CMAKE_MODULE_PATH "${river_SOURCE_DIR}")
