#include <boost/pfr.hpp>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <variant>

struct Wah {
  int wah;
};

struct Sup {
  Wah first;
  int second;
  int third;
  int forth;
  int fifth;
  int sixth;
  int seventh;
  int eight;
  int nineth;
};

template <typename T, typename TIndexSequence>
struct convert_to_impl;

template <typename T, std::size_t... indices>
struct convert_to_impl<T, std::index_sequence<indices...>> {
  template <template <typename...> typename TContainer>
  using type = TContainer<boost::pfr::tuple_element_t<indices, T>...>;
};

template <typename T, template <typename...> typename TContainer>
struct convert_to {
  using type =
      convert_to_impl<T, std::make_index_sequence<boost::pfr::tuple_size_v<T>>>::template type<
          TContainer>;
};
template <typename T, template <typename...> typename TContainer>
using convert_to_t = convert_to<T, TContainer>::type;

template <typename>
struct print_type;

template <typename T>
constexpr auto update_for() {
  return [](T &value, convert_to_t<T, std::variant> const &event) {
    [&]<std::size_t... indices>(std::index_sequence<indices...>) {
      ([&] {
        if (indices == event.index()) {
          boost::pfr::get<indices>(value) = std::get<indices>(event);
          return true;
        }
        return false;
      }()
       || ...);
    }(std::make_index_sequence<boost::pfr::tuple_size_v<T>>{});
  };
}

#define ENABLE_JSON(type)                                                                          \
  template <typename TJson>                                                                        \
  void to_json(TJson &j, type const &value) {                                                      \
    boost::pfr::for_each_field(                                                                    \
        value,                                                                                     \
        [&j]<std::size_t index>(auto const &member, std::integral_constant<std::size_t, index>) {  \
          j[boost::pfr::get_name<index, Sup>()] = member;                                          \
        });                                                                                        \
  }                                                                                                \
  template <typename TJson>                                                                        \
  void from_json(TJson const &j, type &value) {                                                    \
    boost::pfr::for_each_field(                                                                    \
        value, [&j]<std::size_t index>(auto &member, std::integral_constant<std::size_t, index>) { \
          member = j[boost::pfr::get_name<index, Sup>()];                                          \
        });                                                                                        \
  }

ENABLE_JSON(Wah)
ENABLE_JSON(Sup)

namespace fmt {
template <>
struct formatter<Wah> {
  template <typename Context>
  constexpr auto parse(Context &context) -> decltype(context.begin()) {
    return context.begin();
  }
  auto format(Wah const &value, format_context &context) const -> decltype(context.out()) {
    boost::pfr::for_each_field(
        value,
        [&context]<std::size_t index>(auto const &member,
                                      std::integral_constant<std::size_t, index>) {
          fmt::format_to(
              context.out(), "{{\"{}\": {}}}", boost::pfr::get_name<index, Sup>(), member);
        });
    return context.out();
  }
};
template <>
struct formatter<Sup> {
  template <typename Context>
  constexpr auto parse(Context &context) -> decltype(context.begin()) {
    return context.begin();
  }
  auto format(Sup const &value, format_context &context) const -> decltype(context.out()) {
    boost::pfr::for_each_field(
        value,
        [&context]<std::size_t index>(auto const &member,
                                      std::integral_constant<std::size_t, index>) {
          fmt::format_to(
              context.out(), "{{\"{}\": {}}}", boost::pfr::get_name<index, Sup>(), member);
          if constexpr (index != boost::pfr::tuple_size_v<Sup> - 1) {
            fmt::format_to(context.out(), ", ");
          }
        });
    return context.out();
  }
};
} // namespace fmt

int main() {
  using Event = convert_to_t<Sup, std::variant>;
  auto event  = Event{std::in_place_index<8>, 1};

  auto state = Sup{};

  fmt::print("{}\n", state);
  constexpr auto update = update_for<Sup>();
  update(state, event);
  fmt::print("{} {}\n", state.first.wah, state.second);
  event = Event{std::in_place_index<0>, 1};
  update(state, event);
  fmt::print("{} {}\n", state.first.wah, state.second);
  auto json = nlohmann::ordered_json(state);
  fmt::print("{}\n", json.dump());

  auto s = json.get<Sup>();
  fmt::print("{} {}\n", s.first.wah, s.second);
}
