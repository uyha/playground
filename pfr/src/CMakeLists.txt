include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(pfr REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt pfr::pfr nlohmann_json::nlohmann_json)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})

target_precompile_headers(main PUBLIC
  <boost/pfr.hpp>
  <nlohmann/json.hpp>
)
