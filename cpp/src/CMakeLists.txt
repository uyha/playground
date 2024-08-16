include(Conan)
include(CompileOptions)

find_package(fmt REQUIRED)
find_package(Threads)
find_package(msgpack REQUIRED)
find_package(lely-core REQUIRED)
find_package(re2 REQUIRED)
find_package(flatbuffers REQUIRED)
find_package(pfr REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(inja REQUIRED)
find_package(cppzmq REQUIRED)

file(DOWNLOAD
  "https://raw.githubusercontent.com/uyha/fn/v0.5/src/river/fn.hpp"
  "${CMAKE_CURRENT_BINARY_DIR}/external/river/fn.hpp"
  EXPECTED_HASH SHA256=a0f7f00670c08539191cf39bdf6f45894fd9b242fe3c9a337cf48267f403e881
)

function(add_snippet name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} PRIVATE fmt::fmt)
  target_compile_features(${name} PRIVATE cxx_std_20)
  target_compile_options(${name} PRIVATE ${warnings} ${wae})
  target_include_directories(${name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/external")
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
target_link_libraries(msgpack PRIVATE msgpack-cxx)

add_snippet(lely-core)
target_link_libraries(lely-core PRIVATE lely-core::lely-core)

add_snippet(exec)
add_snippet(timerfd)

add_snippet(lambda)

add_snippet(span_string_literal)
add_snippet(customization)

add_snippet(re)
target_link_libraries(re PRIVATE re2::re2)

add_snippet(flatbuffers)
target_link_libraries(flatbuffers PRIVATE flatbuffers::flatbuffers)

add_snippet(variant)

add_snippet(fn)

add_snippet(megameta)
target_link_libraries(megameta PRIVATE pfr::pfr nlohmann_json::nlohmann_json)

add_snippet(arrow_star)
add_snippet(virtual_no_allocate)

add_snippet(inja)
target_link_libraries(inja PRIVATE pantor::inja)
target_precompile_headers(inja PRIVATE
  [[<fmt/core.h>]]
  [[<inja/inja.hpp>]]
)

add_snippet(threaded_inf_loop)
target_link_libraries(threaded_inf_loop PRIVATE Threads::Threads)

add_snippet(suicide)
target_compile_options(suicide PRIVATE -fsanitize=address)
target_link_options(suicide PRIVATE -fsanitize=address)

add_snippet(fork)
target_link_libraries(fork PRIVATE Threads::Threads)

add_snippet(json)
target_link_libraries(json PRIVATE nlohmann_json::nlohmann_json)

add_snippet(metastruct)
target_link_libraries(metastruct PRIVATE pfr::pfr)

add_snippet(function)

add_snippet(member_ptr)
target_link_libraries(member_ptr PRIVATE pfr::pfr)
