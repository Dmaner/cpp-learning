#include <iostream>

template <typename T, typename... Args>
void foo(const T& t, const Args&... reset) {
  std::cout << "Args counts: " << sizeof...(Args) << std::endl;
  std::cout << "args counts: " << sizeof...(reset) << std::endl;
}

template <typename T>
std::ostream& print(std::ostream& os, const T& t)
{
    return os << t;
}

template <typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... reset) {
  os << t << ", ";
  return print(os, reset...);
}

void exc_16_51() {
  std::cout << "Exercise 16.51\n";
  int i = 0;
  double d = 3.14;
  std::string s = "how";
  foo(i, s, 42, d);
  foo(s, 42, "hi");
  foo(d, s);
  foo("hi");
  foo(i, s, s, d);
}

void exc_16_53() {
  std::cout << "Exercise 16.53\n";
  print(std::cout, 1) << std::endl;
  print(std::cout, 1, 2) << std::endl;
  print(std::cout, 1, 2, 3, 4, "sss", 42.4242) << std::endl;
}

int main(int argc, char const* argv[]) {
  exc_16_51();
  exc_16_53();
  return 0;
}
