cmake_minimum_required(VERSION 3.25)
project(neobot
        VERSION 2.0.0
        LANGUAGES CXX)
include(FetchContent)
FetchContent_Declare(river
                     URL file:///home/uy/Personal/cmake-modules
                     )
FetchContent_MakeAvailable(river)
list(APPEND CMAKE_MODULE_PATH "${river_SOURCE_DIR}")
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(Conan)
