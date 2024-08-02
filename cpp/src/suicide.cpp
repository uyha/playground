#include <fmt/core.h>
#include <functional>
#include <map>
#include <memory>

using Slot = std::unique_ptr<std::function<void()>>;

struct Rando {
  std::map<int *, Slot> map{};

  auto eraser(int *ptr) {
    return [this, ptr] {
      fmt::print("{} {} {}\n", map.size(), (void *)this, (void *)ptr);
      map.erase(ptr);
      fmt::print("{} {} {}\n", map.size(), (void *)this, (void *)ptr);
    };
  }
};

template <typename Fn>
auto insert(std::map<int *, Slot> &map, int *key, Fn &&fn) {
  map.insert({key, std::make_unique<std::function<void()>>(std::move(fn))});
}

int main() {
  auto a  = 1;
  auto *b = &a;

  auto c  = 1;
  auto *d = &c;

  auto rando  = Rando{};
  auto eraser = rando.eraser(b);

  insert(rando.map, b, rando.eraser(b));

  eraser();

  insert(rando.map, b, rando.eraser(d));

  eraser();
}
