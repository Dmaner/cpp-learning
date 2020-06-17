#include <iostream>
#include <utility>

// exercise 16.41
template <typename T1, typename T2>
auto sum(T1 a, T2 b) -> decltype(a + b) {
  return a + b;
}

// exercise 16.47

void fuc(int& a, int b) {
  std::cout << "A: " << a << std::endl;
  a = b;
  std::cout << "A: " << a << std::endl;
}

template <typename F, typename T1, typename T2>
void filp(F f, T1&& arg1, T2&& arg2) {
  f(std::forward<T2>(arg2), std::forward<T1>(arg1));
}

int main(int argc, char const* argv[]) {
  int a = 1;
  filp(fuc, 2, a);
  return 0;
}
