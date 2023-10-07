#include <boost/sml.hpp>
#include <fmt/printf.h>

struct e1 {
  int number;
};

constexpr auto even  = [](e1 e) { return e.number % 2 == 0; };
constexpr auto third = [](e1 e) { return e.number % 3 == 0; };
constexpr auto forth = [](e1 e) { return e.number % 4 == 0; };
constexpr auto fifth = [](e1 e) { return e.number % 5 == 0; };

struct Child {
  struct s1 {};

  auto operator()() {
    using namespace boost::sml;
    return make_transition_table(
        *state<s1> + on_entry<_> / [] {},
        state<s1>
            + event<e1>[even and forth] /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  });
  }
};

struct Parent {
  struct s1 {};

  auto operator()() {
    using namespace boost::sml;
    return make_transition_table(*state<Child> + event<e1>[third] / [] {
      fmt::print("{}:{}\n", __FILE__, __LINE__);
      (void)::fflush(::stdout);
    });
  }
};

int main() {
  auto sm = boost::sml::sm<Parent>{};
  sm.process_event(e1{6});
  sm.process_event(e1{4});
}
