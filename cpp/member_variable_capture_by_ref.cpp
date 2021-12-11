#include <iostream>
struct test {

  int m_var = 0;

  void fn() {
    [&var = m_var] { ++var; }();
  }
};

int main() {
  test t{};
  std::cout << t.m_var << std::endl;
  t.fn();
  std::cout << t.m_var << std::endl;
  t.fn();
  std::cout << t.m_var << std::endl;
}
