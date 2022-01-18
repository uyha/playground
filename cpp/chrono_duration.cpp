#include<chrono>

struct Duration{
  std::chrono::steady_clock::duration duration;
};

/* template<Duration duration> */
/* bool test(){ */
/*   using namespace std::chrono_literals; */

/*   return duration.duration > 2s; */
/* } */

int main(){
  using namespace std::chrono_literals;

  constexpr auto duration = Duration{.duration = 20s};
  /* test<duration>(); */

}
