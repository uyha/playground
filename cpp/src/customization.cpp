#include <type_traits>

struct nope;

template <typename T>
struct Serializer {
  Serializer() = delete;
};

template <typename T>
concept Serializable = std::is_constructible_v<Serializer<T>>
                   and requires(T t, Serializer<T> serializer) { serializer(t); };

template <>
struct Serializer<int> {
  auto operator()(int) {};
};

int main() {
  static_assert(Serializable<int>);
}
