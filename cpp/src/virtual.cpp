#include <fmt/core.h>
#include <memory>
#include <river/fn.hpp>

class LLDriver {
public:
  LLDriver(int) {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }

  LLDriver(LLDriver const &)                     = delete;
  auto operator=(LLDriver const &) -> LLDriver & = delete;

  LLDriver(LLDriver &&)                     = delete;
  auto operator=(LLDriver &&) -> LLDriver & = delete;

  virtual ~LLDriver() = default;

  virtual auto check_this() -> void = 0;
};

class VersionedLLDriver : public virtual LLDriver {
public:
  VersionedLLDriver()
      : LLDriver(0) {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }

  auto check_this() -> void override final {
    fmt::print("Checking this\n");
  }
};

class Driver : public virtual LLDriver {
public:
  virtual auto do_this() -> void = 0;
};

class ConcreteDriver
    : public Driver
    , public VersionedLLDriver {
public:
  ConcreteDriver()
      : LLDriver(0)
      , Driver{}
      , VersionedLLDriver{} {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }

  auto do_this() -> void override {
    fmt::print("Doing this\n");
  }
};

int main() {
  std::unique_ptr<Driver> b = std::make_unique<ConcreteDriver>();
  b->check_this();
  b->do_this();
}
