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
template <auto fn>
class ProduceImpl
    : river::fn<fn>
    , public boost::sml::front::action_base {
public:
  template <class Event, class TSM, class TDeps, class TSubs>
  constexpr void operator()(const Event &event, TSM &sm, TDeps &deps, TSubs &subs) {
    using namespace boost::sml::aux;
    using namespace boost::sml::front;

    get<get_root_sm_t<TSubs>>(subs).process_.push([&, this]<typename... Args>(river::type_list<Args...>) {
      return river::fn<fn>::operator()(get_arg(type<Args>{}, event, sm, deps)...);
    }(typename river::fn_trait_of<river::fn<fn>{}>::arguments{}));
  }
};
} // namespace detail

template <auto fn>
static constexpr auto produce = detail::ProduceImpl<fn>();

struct e2 {};

struct State {
  e2 e{};
};

auto fn(State) {
  return e2{};
}

template <auto fn>
struct Produce {
public:
  constexpr auto operator()() const {
    using namespace boost::sml;

    return []<typename... Args>(river::type_list<Args...>) {
      return make_transition_table(
          *state<entry> + on_entry<_> / produce<fn>,
          // This is a workaround since the `sml` library doesn't register the
          // dependencies to its object pool which leads to compilation error, the
          // following transition forces `sml` to register the arguments needed for the
          // `ProduceImpl` to be callable. Check
          // https://github.com/boost-ext/sml/issues/437 for more details
          state<never> + event<never> / [](Args...) {});
    }(typename river::fn_trait_of<river::fn<fn>{}>::arguments{});
  }

private:
  struct entry {};

  struct never {};
};

struct e1 {};

#define line [] { fmt::print("{}\n", __LINE__); }

struct Demo {
  struct s1 : Produce<[] { return e1{}; }> {};

  auto operator()() const {
    using namespace boost::sml;

    return make_transition_table(*state<s1> + event<e1> / line);
  }
};

int main() {
  using namespace boost::sml;

  auto demo = sm<Demo, process_queue<std::queue>>{};
}
