#include <type_traits>

#define IPCPP_BITOR_OVERRIDE(_1, _2, _3, NAME, ...) NAME

#define IPCPP_BITOR_OP_IMPL(left_type, right_type, return_type)                \
  constexpr auto operator|(left_type lhs,                                      \
                           right_type rhs) noexcept->return_type {             \
    return static_cast<return_type>(                                           \
        static_cast<std::underlying_type_t<left_type>>(lhs) |                 \
        static_cast<std::underlying_type_t<right_type>>(rhs));                 \
  }

#define IPCPP_SAME_TYPE_BITOR_OP(input_type, return_type)                      \
  IPCPP_BITOR_OP_IMPL(input_type, input_type, return_type)
#define IPCPP_DIFF_TYPE_BITOR_OP(left_type, right_type, return_type)           \
  IPCPP_BITOR_OP_IMPL(left_type, right_type, return_type)                      \
                                                                               \
  constexpr auto operator|(right_type lhs,                                     \
                           left_type rhs) noexcept->return_type {              \
    return rhs | lhs;                                                          \
  }

#define IPCPP_BITOR_OP(...)                                                    \
  IPCPP_BITOR_OVERRIDE(__VA_ARGS__, IPCPP_DIFF_TYPE_BITOR_OP,                  \
                       IPCPP_SAME_TYPE_BITOR_OP)                               \
  (__VA_ARGS__)

enum class A : int { a, b };
enum class B : int { a, b };
IPCPP_BITOR_OP(A, A)
IPCPP_BITOR_OP(A, B, B)

int main() { A::a | A::b; }
