#include <iostream>
#include <scope.hpp>

int main() {
  auto first  = scope::scope_exit{[]() { std::cout << __FILE__ << ":" << __LINE__ << std::endl; }};
  auto second = scope::scope_exit{[]() { std::cout << __FILE__ << ":" << __LINE__ << std::endl; }};
  auto third  = scope::scope_success{[]() { std::cout << __FILE__ << ":" << __LINE__ << std::endl; }};
  auto fourth = scope::scope_fail{[]() { std::cout << __FILE__ << ":" << __LINE__ << std::endl; }};
}
