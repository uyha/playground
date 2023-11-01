include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)

file(DOWNLOAD
  "https://raw.githubusercontent.com/uyha/fn/v0.5/src/river/fn.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/include/river/fn.hpp"
  EXPECTED_HASH SHA256=a0f7f00670c08539191cf39bdf6f45894fd9b242fe3c9a337cf48267f403e881
)

file(DOWNLOAD
  "https://raw.githubusercontent.com/boost-ext/sml2/main/sml2"
  "${CMAKE_CURRENT_BINARY_DIR}/include/boost/sml.hpp"
  EXPECTED_HASH SHA256=1e46cd2574e0b99ff5a58bf80923ef42e238d933340494656054b3f761179291
)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt)
target_include_directories(main PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
