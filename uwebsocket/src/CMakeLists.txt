include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(uwebsockets REQUIRED)
find_package(Threads REQUIRED)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE Threads::Threads fmt::fmt uwebsockets::uwebsockets)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
