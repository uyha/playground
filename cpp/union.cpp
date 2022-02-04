#include <iostream>
#include <cstdint>
#include <array>
#include <bit>

union Bytes {
  int i;
  std::string s;
  ~Bytes(){}
};

int main(){
  auto bytes = Bytes{1};
  std::cout << bytes.s;
}
