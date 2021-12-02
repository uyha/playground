#include <type_traits>

template<typename T>
struct Wrapper{
  using type = T;
};

struct C{
  using A = Wrapper<struct B>;
};
struct D{
  using A = Wrapper<struct B>;
};

int main(){
  static_assert(std::is_same_v<C::A::type, D::A::type>);
}
