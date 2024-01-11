

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "enum.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "enum.cpp2"
[[nodiscard]] auto in_auto(cpp2::in<cpp2::u64> i) -> bool;

//=== Cpp2 function definitions =================================================

#line 1 "enum.cpp2"
[[nodiscard]] auto in_auto(cpp2::in<cpp2::u64> i) -> bool{
#line 2 "enum.cpp2"
  return !((i & (1 << 25))); 
}

