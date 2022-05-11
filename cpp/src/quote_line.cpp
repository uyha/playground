#include <fmt/format.h>

#define QUOTE(s) #s
#define NAME_IMPL(s) QUOTE(s)
#define NAME NAME_IMPL(__LINE__)

int main(){
  fmt::print("{}\n", NAME);
}
