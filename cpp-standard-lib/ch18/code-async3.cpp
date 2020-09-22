#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

void doSomething(char c) {
  default_random_engine dre(c);
  uniform_int_distribution<int> id(10, 1000);

  for (int i = 0; i < 10; i++) {
    this_thread::sleep_for(chrono::milliseconds(id(dre)));
    cout.put(c).flush();
  }
}

int main(int argc, char const *argv[]) {
  auto f1 = async([] { doSomething('.');});
  auto f2 = async([] { doSomething('+');});
  if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
      f2.wait_for(chrono::seconds(0)) != future_status::deferred) {
    while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
           f2.wait_for(chrono::seconds(0)) != future_status::ready)
      this_thread::yield();
  }
  f1.get();
  f2.get();
  return 0;
}
