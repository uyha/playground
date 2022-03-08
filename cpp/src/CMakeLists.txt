include(build_options)
include(use_conan)

find_package(fmt)
find_package(Threads)

function(add_snippet name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} PRIVATE fmt::fmt)
  target_compile_features(${name} PRIVATE cxx_std_20)
  target_compile_options(${name} PRIVATE ${warnings} ${wae})
endfunction()

add_snippet(conditional_variable)
target_link_libraries(conditional_variable PRIVATE Threads::Threads)

add_snippet(epoll)
target_link_libraries(epoll PRIVATE rt)

add_snippet(fmt_string_view)
target_link_libraries(fmt_string_view PRIVATE fmt::fmt)

add_snippet(macros)
target_compile_definitions(macros PRIVATE SANDBOX_LED_3)

add_snippet(chrono)
add_snippet(unique_macro)

add_snippet(pthread_rwlock)
target_link_libraries(pthread_rwlock PRIVATE Threads::Threads)
