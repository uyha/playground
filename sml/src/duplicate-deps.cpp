#include <boost/sml.hpp>

struct s1 {};
struct s2 {};

struct e1 {};
struct e2 {};

struct A {};
struct B {
  B(A) {}
};

struct StateMachine {
  auto operator()() const {
    using namespace boost::sml;

    auto guard = [](A const &) { return true; };

    return make_transition_table(
        *state<s1> + event<A>[guard] = state<s2>,
        state<s1> + event<e2> / [](B const &) {},
        state<s2> + event<e2> / [](B const &) {});
  };
};

int main() {
  auto a = A{};
  auto b = B{a};

  auto state_machine = boost::sml::sm<StateMachine>{a, b};
  state_machine.process_event(e1{});
}
