#include <boost/sml.hpp>
#include <fmt/printf.h>
#include <queue>

struct e1 {};

struct StateMachine {
  struct Entry {};
  struct Second {};

  auto operator()() const {
    using namespace boost::sml;
    return make_transition_table(*state<Entry> / [] {
      fmt::print("{}:{}\n", __FILE__, __LINE__);
      (void)::fflush(::stdout);
    } = state<Second>);
  };
};

int main() {
  auto state_machine = boost::sml::sm<StateMachine, boost::sml::process_queue<std::queue>>{};
}
