#include <fmt/format.h>
#include <functional>

template <std::size_t size>
struct Wrapper {
  char const data[size];
  std::size_t data_size = sizeof(data);
};

template <std::size_t size>
Wrapper(char const (&)[size]) -> Wrapper<size>;

template <typename TFn>
class Callable {
public:
  Callable(TFn &&fn)
      : m_fn{std::move(fn)} {}

  template <typename... TParams>
  auto operator()(TParams &&...params)
    requires(std::invocable<TFn, decltype(params)...>)
  {
    std::invoke(m_fn, std::forward<TParams>(params)...);
  }

private:
  TFn m_fn;
};

template <typename TFn>
Callable(TFn) -> Callable<TFn>;

int main() {
  auto call = Callable{[] { fmt::print("Hello\n"); }};
  call();

  fmt::print("{}\n", sizeof(call));
  fmt::print("{}\n", sizeof([] {}));
}
