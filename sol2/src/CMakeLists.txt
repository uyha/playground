include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(sol2 REQUIRED)


add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt sol2::sol2)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
target_precompile_headers(main
  PRIVATE
    <fmt/format.h>
    <sol/sol.hpp>
)
