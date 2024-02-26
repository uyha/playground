find_package(ZLIB REQUIRED)

add_library(gzip INTERFACE)
add_library(gzip::gzip ALIAS gzip)
target_include_directories(gzip INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(gzip INTERFACE ZLIB::ZLIB)
target_compile_features(gzip INTERFACE cxx_std_20)

