include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(cppzmq REQUIRED)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt cppzmq)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
