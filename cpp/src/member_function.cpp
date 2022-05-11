struct A {
  void f() {}
};

template <typename T, typename TObj, typename... Args>
void f(T t, TObj obj, Args... args) {
  (obj.*t)(args...);
}

int main() {
  A a{};
  f(&A::f, a);
}
