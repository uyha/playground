#include <boost/sml.hpp>
#include <fmt/printf.h>

namespace sml = boost::sml;

struct Child {
  constexpr auto operator()() const {
    using namespace boost::sml;
    return make_transition_table(
        *state<entry>
            + on_entry<_> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  },
        state<entry>
            + sml::on_exit<_> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  });
  }

private:
  struct entry {};
};

struct Derived : Child {};

struct e1 {};

struct Parent {
  constexpr auto operator()() const {
    using namespace sml;
    return make_transition_table(*state<Derived> + event<e1> = state<Other>, state<Other> + event<e1> = state<Derived>);
  }

private:
  struct Other {};
};

int main() {
  auto sm = sml::sm<Parent>{};
  sm.process_event(e1{});
  sm.process_event(e1{});
  sm.process_event(e1{});
}
