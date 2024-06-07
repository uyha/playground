#include <boost/pfr.hpp>
#include <nlohmann/json.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

namespace pfr = boost::pfr;
using json    = nlohmann::json;

struct Sub {
  int b = 1;
};

struct Config {
  int a;
  Sub b;
};

template <typename T, typename TJson>
concept JsonPrimitive =
    std::convertible_to<T, typename TJson::object_t> or std::convertible_to<T, typename TJson::array_t>
    or std::convertible_to<T, typename TJson::string_t> or std::convertible_to<T, typename TJson::boolean_t>
    or std::convertible_to<T, typename TJson::number_integer_t>
    or std::convertible_to<T, typename TJson::number_unsigned_t>
    or std::convertible_to<T, typename TJson::number_float_t> or std::convertible_to<T, typename TJson::binary_t>;

namespace nlohmann {
template <typename T>
struct adl_serializer<T> {
  template <typename TJson>
  static void to_json(TJson &j, T const &value) {
    if constexpr (JsonPrimitive<T, TJson>) {
      using nlohmann::to_json;
      to_json(j, value);
    } else {
      pfr::for_each_field(value,
                          [&j]<std::size_t index>(auto const &field, std::integral_constant<std::size_t, index>) {
                            j[pfr::get_name<index, T>()] = field;
                          });
    }
  }

  template <typename TJson>
  static void from_json(TJson const &j, T &value) {
    if constexpr (JsonPrimitive<T, TJson>) {
      using nlohmann::from_json;
      from_json(j, value);
    } else {
      pfr::for_each_field(value,
                          [&j]<typename TField, std::size_t index>(TField &field,
                                                                   std::integral_constant<std::size_t, index>) {
                            using nlohmann::from_json;
                            field = j[pfr::get_name<index, T>()].template get<TField>();
                          });
    }
  }
};
} // namespace nlohmann

int main() {
  auto a = json{};
  a      = Config{};
  fmt::print("{}\n", a.get<Config>().a);
}
