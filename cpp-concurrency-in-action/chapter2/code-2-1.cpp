#include <chrono>
#include <iostream>
#include <thread>

// 线程在后台运行时，可能访问已经销毁的变量

void do_something(int& i) { ++i; }

struct func {
  int& i;

  func(int& i_) : i(i_) {}

  void operator()() {
    for (unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
      if (i % 10000 == 0) std::cout << "Value i : " << i << std::endl;
    }
  }
};

void oops() {
  using namespace std::chrono_literals;
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();
  std::this_thread::sleep_for(0.01s);
  std::cout << "Finish oops\n";
}

int main() { oops(); }