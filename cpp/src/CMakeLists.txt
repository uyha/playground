include(build_options)
include(use_conan)

find_package(fmt)
find_package(Threads)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE fmt::fmt Threads::Threads)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE ${warnings} ${wae})
