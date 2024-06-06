include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(cppzmq REQUIRED)

add_executable(req-rep "req-rep.cpp")
target_link_libraries(req-rep PRIVATE fmt::fmt cppzmq)
target_compile_features(req-rep PRIVATE cxx_std_20)
target_compile_options(req-rep PRIVATE ${warnings} ${wae})

add_executable(push-pull "push-pull.cpp")
target_link_libraries(push-pull PRIVATE fmt::fmt cppzmq)
target_compile_features(push-pull PRIVATE cxx_std_20)
target_compile_options(push-pull PRIVATE ${warnings} ${wae})

add_executable(barebone "barebone.cpp")
target_link_libraries(barebone PRIVATE cppzmq)
target_compile_features(barebone PRIVATE cxx_std_20)
target_compile_options(barebone PRIVATE ${warnings} ${wae})
