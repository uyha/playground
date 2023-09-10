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
  EXPECTED_HASH SHA256=1112fbcbab738c013531313175f33e435945e52db632e41e75f4782838d79039
)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})

add_executable(sandbox-sml sml.cpp)
target_link_libraries(sandbox-sml PRIVATE fmt::fmt)
target_include_directories(sandbox-sml PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_compile_features(sandbox-sml PUBLIC cxx_std_20)
target_compile_options(sandbox-sml PRIVATE ${warnings} ${wae})

add_executable(sandbox-entry-exit entry-exit.cpp)
target_link_libraries(sandbox-entry-exit PRIVATE fmt::fmt)
target_include_directories(sandbox-entry-exit PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_compile_features(sandbox-entry-exit PRIVATE cxx_std_20)
target_compile_options(sandbox-entry-exit PRIVATE ${warnings} ${wae})
