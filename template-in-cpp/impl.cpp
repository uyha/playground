#include "decl.hpp"

template <typename>
void fun() {}

template void fun<int>();
template void fun<float>();
