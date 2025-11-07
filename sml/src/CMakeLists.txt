include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(sml REQUIRED)

file(DOWNLOAD
  "https://raw.githubusercontent.com/uyha/fn/v0.3/src/river/fn.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/include/river/fn.hpp"
  EXPECTED_HASH SHA256=8edfdb83d7803db812446d467c9ef85d86427f55fe805ffd9e971fe0a640dbca
)

function(add_sandbox name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} PRIVATE sml::sml fmt::fmt)
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
  target_compile_features(${name} PRIVATE cxx_std_20)
  target_compile_options(${name} PRIVATE ${warnings} ${wae})
endfunction()

add_sandbox(sml)
add_sandbox(entry-exit)
add_sandbox(duplicate-deps)
add_sandbox(child-rejected)
add_sandbox(queued-events)
add_sandbox(child-on-exit)
add_sandbox(immediate)
add_sandbox(any)
