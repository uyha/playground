include(build_options)
include(use_conan)

find_package(fmt)
find_package(Threads)

add_executable(conditional_variable "conditional_variable.cpp")
target_link_libraries(conditional_variable PRIVATE fmt::fmt Threads::Threads)
target_compile_features(conditional_variable PRIVATE cxx_std_20)
target_compile_options(conditional_variable PRIVATE ${warnings} ${wae})
