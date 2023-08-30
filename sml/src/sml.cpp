#include <concepts>
#include <queue>
#include <utility>

#include <boost/sml.hpp>
#include <fmt/printf.h>
#include <river/fn.hpp>

template <typename Expr, typename T = void>
class ExtractImpl : boost::sml::front::action_base {
public:
  template <typename R, typename... Args, typename Fn>
    requires(std::invocable<Fn, Args...> and std::is_same_v<std::invoke_result_t<Fn, Args...>, R>)
  constexpr explicit ExtractImpl(Fn &&fn)
      : callback{std::forward<Fn>(fn)} {}

private:
  boost::sml::aux::zero_wrapper<Expr, T> callback;
};

template <typename>
struct print_type;

namespace detail {
template <typename Fn, typename T = void>
class Impl
    : boost::sml::aux::zero_wrapper<Fn, T>
    , public boost::sml::front::action_base {
public:
  template <typename TFn>
  constexpr Impl(TFn &&in_fn)
      : boost::sml::aux::zero_wrapper<Fn, T>{std::forward<TFn>(in_fn)} {}

  template <class Event, class TSM, class TDeps, class TSubs>
  constexpr void operator()(const Event &event, TSM &sm, TDeps &deps, TSubs &subs) {
    using namespace boost::sml::aux;
    using namespace boost::sml::front;

    get<get_root_sm_t<TSubs>>(subs).process_.push([&, this]<typename... Args>(river::type_list<Args...>) {
      return zero_wrapper<Fn, T>::operator()(get_arg(type<Args>{}, event, sm, deps)...);
    }(typename river::fn_trait<decltype(&zero_wrapper<Fn, T>::operator())>::arguments{}));
  }
};

} // namespace detail

template <typename Fn>
constexpr auto extract(Fn &&fn) {
  return detail::Impl<Fn, Fn>{std::forward<Fn>(fn)};
}

struct e2 {};

struct State {
  e2 e{};
};

auto fn(State) {
  return e2{};
}

struct SM {
  struct s1 {};
  struct s2 {};

  struct e1 {};
  auto operator()() {
    using namespace boost::sml;
    return make_transition_table(
        *state<s1>
            + event<e1>
                  / (extract([](State state) { return state.e; }),
                     [] {
                       fmt::print("{}:{}\n", __FILE__, __LINE__);
                       (void)::fflush(::stdout);
                     }) = state<s1>,
        state<s1> + event<e2> / [](State &) {
          fmt::print("{}:{}\n", __FILE__, __LINE__);
          (void)::fflush(::stdout);
        } = X);
  }
};

int main() {
  using namespace boost::sml;

  State state{};
  auto s = sm<SM, process_queue<std::queue>>{state};
  s.process_event(SM::e1{});
}
