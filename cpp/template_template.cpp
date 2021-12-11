#include <chrono>
#include <iostream>
#include <type_traits>

template <typename T> struct is_duration : std::false_type {};

template <typename Rep, typename Period>
struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

template <typename T>
concept Duration = is_duration<T>::value;

int main() { std::cout << Duration<std::chrono::steady_clock::duration>; }
