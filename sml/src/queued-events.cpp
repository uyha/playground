#include <queue>

#include <boost/sml.hpp>
#include <fmt/printf.h>

namespace sml = boost::sml;

struct Child {
  struct s1 {};

  struct e1 {
    int a;
  };
  auto operator()() {
    using namespace sml;

    return make_transition_table(*state<s1> + event<e1> / [](e1 const &e) {
      fmt::print("{}:{} {}\n", __FILE__, __LINE__, e.a);
      (void)::fflush(::stdout);
    });
  }
};

struct Parent {
  struct s1 {};
  struct e1 {};

  auto operator()() {
    using namespace sml;

    return make_transition_table(*state<s1> + event<e1> / process(Child::e1{.a = 100}) = state<Child>);
  }
};

int main() {
  auto sm = sml::sm<Parent, sml::process_queue<std::queue>>{};
  sm.process_event(Parent::e1{});
}
