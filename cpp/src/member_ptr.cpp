#include <boost/pfr.hpp>
#include <fmt/core.h>
#include <fmt/std.h>

template <typename T, typename TMember>
auto get(T const &value, TMember T::*ptr) -> TMember const & {
  return value.*ptr;
}

struct A {
  int b;
  int c;

  int d();
};

template <auto>
struct print_type;

namespace boost::pfr {
template <class T, auto ptr>
consteval auto index_impl(T const &val) {
  auto found  = false;
  auto result = 0;

  boost::pfr::for_each_field(
      val, [&]<std::size_t index>(auto &&member, std::integral_constant<std::size_t, index>) {
        if (std::addressof(member) == std::addressof(val.*ptr)) {
          found  = true;
          result = index;
        }
      });

  if (!found) {
    throw std::exception{};
  }

  return result;
}

template <typename T, typename TMember>
auto class_of(TMember T::*) -> T;

template <auto ptr>
  requires std::is_member_object_pointer_v<decltype(ptr)>
constexpr auto index = index_impl<decltype(class_of(&A::b)), ptr>(
    boost::pfr::detail::fake_object<decltype(class_of(&A::b))>);
} // namespace boost::pfr

int main() {
  fmt::print("{}:{} {}\n", __FILE__, __LINE__, boost::pfr::index<&A::b>);
  (void)::fflush(::stdout);
}
