include(CompileOptions)
include(Conan)

find_package(fmt REQUIRED)
find_package(Threads)
find_package(msgpack REQUIRED)
find_package(lely-core REQUIRED)

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

add_snippet(sanitizer)
target_compile_options(sanitizer PRIVATE -fsanitize=address,undefined,enum,shift)
target_link_options(sanitizer PRIVATE -fsanitize=address,undefined,enum,shift)

add_snippet(message_queue)
target_link_libraries(message_queue PRIVATE rt)

add_snippet(fstat)
target_link_libraries(fstat PRIVATE rt)

add_snippet(ftruncate)
target_link_libraries(ftruncate PRIVATE rt)

add_snippet(error_code)
target_sources(error_code PRIVATE error_code.impl.cpp)

add_snippet(fchown)
target_link_libraries(fchown PRIVATE rt)

add_snippet(flock)
target_link_libraries(flock PRIVATE rt)

add_snippet(benchmark)
target_link_libraries(benchmark PRIVATE rt)


add_snippet(member_function)
add_snippet(unix_socket_dgram_server)
add_snippet(unix_socket_dgram_client)

add_snippet(unix_socket_stream_server)
add_snippet(unix_socket_stream_client)

add_snippet(socket)

add_snippet(quote_line)

add_snippet(protocol_entry)

add_snippet(variadic_template)
add_snippet(ctad)
add_snippet(padding)
add_snippet(un)

add_snippet(member_count)

add_snippet(msgpack)
target_link_libraries(msgpack PRIVATE msgpackc-cxx)

add_snippet(lely-core)
target_link_libraries(lely-core PRIVATE lely-core::lely-core)

add_snippet(exec)
add_snippet(timerfd)

add_snippet(lambda)
