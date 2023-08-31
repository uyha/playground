include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(sml REQUIRED)

file(DOWNLOAD
  "https://raw.githubusercontent.com/uyha/fn/v0.3/src/river/fn.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/include/river/fn.hpp"
  EXPECTED_HASH SHA256=8edfdb83d7803db812446d467c9ef85d86427f55fe805ffd9e971fe0a640dbca
)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})

add_executable(sandbox-sml sml.cpp)
target_link_libraries(sandbox-sml PRIVATE sml::sml fmt::fmt)
target_include_directories(sandbox-sml PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_compile_features(sandbox-sml PRIVATE cxx_std_20)
target_compile_options(sandbox-sml PRIVATE ${warnings} ${wae})
