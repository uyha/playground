include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(reflect-cpp REQUIRED)
find_package(msgpack-cpp REQUIRED)

add_executable(main "main.cpp")
target_link_libraries(main
  PRIVATE
    fmt::fmt
    reflect-cpp::reflect-cpp
    msgpack-cpp:msgpack-cpp
)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
target_precompile_headers(main
  PRIVATE
    <rfl/json.hpp>
)
