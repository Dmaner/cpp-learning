#include <iostream>
#include <random>
#include <thread>

void do_something(int& i) { ++i; }

struct func {
  int& i;

  func(int& i_) : i(i_) {}

  void operator()() {
    std::cout << "Thread begin working..." << std::endl;
    for (unsigned j = 0; j < 100000; ++j) {
      do_something(i);
    }
  }
};

void do_something_in_current_thread() {
  if (std::rand() % 2 != 0)
    std::cout << "No exception" << std::endl;
  else
    throw "Oops! throw error!";
}

void f() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try {
    do_something_in_current_thread();
  } catch (const char* msg) {
    t.join();
    std::cerr << msg << std::endl;
  }
  t.join();
}

int main() {
  std::srand(time(0));
  std::cout << rand() % 2 << std::endl;
  f();
}