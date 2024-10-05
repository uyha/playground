#pragma once

template <typename>
void fun();

template <typename T>
struct A {
  void (*ptr)() = &fun<T>;
};
