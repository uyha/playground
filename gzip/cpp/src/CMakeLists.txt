include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(cppzmq REQUIRED)
find_package(msgpack REQUIRED)

add_executable(main "main.cpp")
target_link_libraries(main
  PRIVATE
    cppzmq
    fmt::fmt
    gzip::gzip
    msgpack-cxx
)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
