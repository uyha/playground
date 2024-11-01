#include <any>
#include <fmt/core.h>
#include <memory>
#include <river/fn.hpp>

class LLDriver {
public:
  virtual ~LLDriver() = 0;
};
LLDriver::~LLDriver() {}

class VersionedLLDriver : public virtual LLDriver {
public:
  VersionedLLDriver()
      : LLDriver{} {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }

  auto check_this() -> void {
    fmt::print("Checking this\n");
  }
};

class Driver : public virtual LLDriver {
public:
  virtual auto do_this() -> void    = 0;
  virtual auto check_this() -> void = 0;
};

class ConcreteDriver
    : public Driver
    , public VersionedLLDriver {
public:
  ConcreteDriver()
      : LLDriver{}
      , Driver{}
      , VersionedLLDriver{} {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }

  auto do_this() -> void override {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
    fmt::print("Doing this\n");
  }
  auto check_this() -> void override {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
    fmt::print("Checking this\n");
  }
};

class Local : public Driver {
public:
  auto do_this() -> void override {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }
  auto check_this() -> void override {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }

  ~Local() noexcept {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }
};
auto create() -> std::unique_ptr<Driver> {
  return std::make_unique<Local>();
}

int main() {
  auto b = create();
  // std::unique_ptr<Driver> b = create<1>();
  // std::unique_ptr<Driver> c = create<2>();
  // b->check_this();
  // b->do_this();
  // c->check_this();
  // c->do_this();
}
