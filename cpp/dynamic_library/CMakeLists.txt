add_library(lang IMPORTED INTERFACE)

add_library(lang_a SHARED lib_a.cpp)
add_library(lang_b SHARED lib.cpp)

add_executable(lang_main main.cpp)
target_link_libraries(lang_main PRIVATE lang_a)
