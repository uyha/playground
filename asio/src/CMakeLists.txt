include(CompileOptions)
include(Conan)

find_package(asio REQUIRED)
find_package(fmt REQUIRED)

add_library(pch dummy.cpp)
target_precompile_headers(pch PUBLIC
  <asio.hpp>
  <chrono>
  <fmt/printf.h>
)
target_link_libraries(pch PRIVATE asio::asio fmt::fmt)
target_compile_features(pch PRIVATE cxx_std_20)
target_compile_options(pch PRIVATE ${warnings} ${wae})

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt asio::asio)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
target_precompile_headers(main REUSE_FROM pch)
