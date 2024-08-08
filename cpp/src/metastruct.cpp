#include <boost/pfr.hpp>
#include <fmt/core.h>
#include <variant>

namespace tyfu {
template <typename>
struct Tag {};

struct DefaultTrait {};

template <typename T>
constexpr auto tyfu_trait(Tag<T>) -> void;

template <typename T>
  requires std::is_enum_v<T>
constexpr auto tyfu_trait(Tag<T>) -> DefaultTrait;
template <std::integral T>
constexpr auto tyfu_trait(Tag<T>) -> DefaultTrait;
template <std::floating_point T>
constexpr auto tyfu_trait(Tag<T>) -> DefaultTrait;

template <typename T>
using Trait = decltype(tyfu_trait(std::declval<Tag<T>>()));

template <typename T>
concept Tyfu = not std::is_same_v<Trait<T>, void>;

namespace detail {
template <Tyfu T, typename TIndexSequence>
struct convert_to_impl;

template <Tyfu T, std::size_t... indices>
struct convert_to_impl<T, std::index_sequence<indices...>> {
  template <template <typename...> typename TContainer>
  using type = TContainer<boost::pfr::tuple_element_t<indices, T>...>;
};
} // namespace detail

template <Tyfu T, template <typename...> typename TContainer>
struct convert_to {
  using type = detail::convert_to_impl<T, std::make_index_sequence<boost::pfr::tuple_size_v<T>>>::
      template type<TContainer>;
};
template <Tyfu T, template <typename...> typename TContainer>
using convert_to_t = convert_to<T, TContainer>::type;

template <Tyfu T, typename TValue>
constexpr auto set(T &source, TValue const &value) -> void {
  [&]<std::size_t... indices>(std::index_sequence<indices...>) {
    ([&] {
      if (indices == value.index()) {
        boost::pfr::get<indices>(source) = std::get<indices>(value);
        return true;
      }
      return false;
    }()
     || ...);
  }(std::make_index_sequence<boost::pfr::tuple_size_v<T>>{});
}
} // namespace tyfu

namespace neobot {
enum class Motor { hdm08, hdm10_i12, hdm10_i16 };
enum class Indicator { led_3, led_2, led_buzzer };
enum class PowerOff { sick, gpio };
enum class RemoteController { hatox, autec };
enum class Battery { aentron, inventus };

struct Config {
  Motor motor;
  Indicator indicator;
  PowerOff power_off;
  RemoteController remote_controller;
  Battery battery;
};

constexpr auto tyfu_trait(tyfu::Tag<Config>) -> tyfu::DefaultTrait;
} // namespace neobot

int main() {
  auto config = neobot::Config{};
  auto value  = tyfu::convert_to_t<neobot::Config, std::variant>{
      neobot::PowerOff::sick,
  };
  tyfu::set(config, value);
}
