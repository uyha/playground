#include <boost/sml.hpp>
#include <fmt/core.h>

using namespace boost::sml;

struct Any {
  struct s1 {};
  struct s2 {};

  struct e1 {};
  struct sync {};

  auto operator()() const {
    return make_transition_table(

        state<_>
            + event<sync> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  },

        *state<s1>
            + on_entry<_> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  },
        state<s1>
            + event<e1> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  } = state<s2>,

        state<s2>
            + on_entry<_> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  });
  }
};

int main() {
  [[maybe_unused]] auto machine = sm<Any>{};

  // machine.process_event(Any::sync{});
  // machine.process_event(Any::e1{});
  // machine.process_event(Any::sync{});

  return 0;
}
