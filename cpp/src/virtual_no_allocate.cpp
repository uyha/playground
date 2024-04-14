#include <fmt/core.h>
class interface {
public:
  virtual auto fn() -> char const * = 0;

  virtual ~interface() = default;
};

class derived : public interface {
public:
  auto fn() -> char const * override {
    return "derived";
  }
};

class derived2 : public interface {
public:
  auto fn() -> char const * override {
    return "derived2";
  }
};

auto invoke(interface &&i) {
  fmt::print("{}\n", i.fn());
}

int main() {
  invoke(derived());
  invoke(derived2());
}
