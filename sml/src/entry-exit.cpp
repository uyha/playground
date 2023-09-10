#include <boost/sml.hpp>
#include <fmt/printf.h>
#include <queue>

struct e1 {};

struct EntryExit {
private:
  struct init {};

public:
  constexpr auto operator()() const {
    using namespace boost::sml;

    return make_transition_table(
        *state<init> + on_entry<_> / process(e1{}),
        state<init>
            + on_entry<_> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  },
        state<init>
            + boost::sml::on_exit<_> /
                  [] {
                    fmt::print("{}:{}\n", __FILE__, __LINE__);
                    (void)::fflush(::stdout);
                  },
        state<init> = X);
  }
};

struct StateMachine {
  constexpr auto operator()() const {
    using namespace boost::sml;
    return make_transition_table(*state<EntryExit> + event<e1> = X);
  };
};

int main() {
  auto state_machine = boost::sml::sm<StateMachine, boost::sml::process_queue<std::queue>>{};
}
