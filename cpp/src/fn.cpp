#include <river/fn.hpp>

struct Selecter {
  static auto select_bind(int &, int) {}
};

template <typename...>
struct print_type;

int main() {
  using Fn = river::fn_trait_of<Selecter::select_bind>;

  auto lambda = []<typename... Args>(river::type_list<int &, Args...>) {};

  lambda(Fn::arguments{});
}
