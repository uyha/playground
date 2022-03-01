#include "sml.hpp"
#include <iostream>
#include <queue>

using namespace boost::sml;

struct Process {};

template <typename> class SendingWithDelay {
public:
  struct Sending {};
  struct Delaying {};

  struct Done {};

  auto operator()() {
    using namespace boost::sml;

    return make_transition_table(
        *state<Sending> +
            event<Process> / [] { std::cout << __LINE__ << " Sending\n"; } =
            state<Delaying>,
        state<Delaying> + event<Process> / process(Done{}) = X);
  }
};

template <typename> class SendingWithDeadline {
public:
  struct Sending {};
  struct Observing {};

  struct Done {};
  struct Expired {};

  auto operator()() {
    using namespace boost::sml;

    return make_transition_table(
        *state<Sending> +
            event<Process> / [] { std::cout << __LINE__ << " Sending\n"; } =
            state<Observing>,
        state<Observing> + event<Process> / process(Done{}) = X);
  }
};

template <typename> struct SendingWithResetting {
  using Sending = SendingWithDeadline<SendingWithResetting>;
  using Resetting = SendingWithDelay<SendingWithResetting>;

  struct Setup {};
  struct Done {};

  auto operator()() {
    using namespace boost::sml;
    return make_transition_table(
        *state<Setup> + event<Process> = state<Sending>,
        state<Sending> + event<typename Sending::Done> / process(Done{}) = X,
        state<Sending> + event<typename Sending::Expired> = state<Resetting>,
        state<Resetting> + event<typename Resetting::Done> = state<Sending>);
  }
};

struct Main {
  using SubState = SendingWithResetting<Main>;
  struct Setup {};
  struct Next {};
  struct Done {};

  auto operator()() {
    using namespace boost::sml;

    return make_transition_table(
        *state<Setup> + event<Process> = state<SubState>,
        state<SubState> + event<SubState::Done> = state<Next>,
        state<Next> + event<Process> / process(Done{}) = X);
  }
};

struct MainMain {
  struct Next {};
  auto operator()() {
    using namespace boost::sml;

    return make_transition_table(*state<Main> + event<Main::Done> = state<Next>,
                                 state<Next> + event<Process> = state<Main>);
  }
};
struct my_logger {
  template <class SM, class TEvent> void log_process_event(const TEvent &) {
    printf("[%s][process_event] %s\n", boost::sml::aux::get_type_name<SM>(),
           boost::sml::aux::get_type_name<TEvent>());
  }

  template <class SM, class TGuard, class TEvent>
  void log_guard(const TGuard &, const TEvent &, bool result) {
    printf("[%s][guard] %s %s %s\n", boost::sml::aux::get_type_name<SM>(),
           boost::sml::aux::get_type_name<TGuard>(),
           boost::sml::aux::get_type_name<TEvent>(),
           (result ? "[OK]" : "[Reject]"));
  }

  template <class SM, class TAction, class TEvent>
  void log_action(const TAction &, const TEvent &) {
    printf("[%s][action] %s %s\n", boost::sml::aux::get_type_name<SM>(),
           boost::sml::aux::get_type_name<TAction>(),
           boost::sml::aux::get_type_name<TEvent>());
  }

  template <class SM, class TSrcState, class TDstState>
  void log_state_change(const TSrcState &src, const TDstState &dst) {
    printf("[%s][transition] %s -> %s\n", boost::sml::aux::get_type_name<SM>(),
           src.c_str(), dst.c_str());
  }
};
int main() {
  my_logger logger{};
  sm<MainMain, process_queue<std::queue>, boost::sml::logger<my_logger>>
      state_machine{logger};
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
  state_machine.process_event(Process{});
}
