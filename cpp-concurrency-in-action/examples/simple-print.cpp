#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mut;
condition_variable cond;
bool flag = true;
int Acount = 0;
int Bcount = 0;

void printA() {
  while (Acount < 3) {
    this_thread::sleep_for(chrono::seconds(1));
    {
      unique_lock<mutex> lock(mut);
      cond.wait(lock, [] { return flag; });
      cout << "Thread A " << this_thread::get_id() << " YYY " << endl;
      flag = false;
      Acount++;
    }
    cond.notify_one();
  }
}

void printB() {
  while (Bcount < 3) {
    this_thread::sleep_for(chrono::seconds(1));
    {
      unique_lock<mutex> lock(mut);
      cond.wait(lock, [] { return !flag; });
      cout << "Thread B " << this_thread::get_id() << " YYY " << endl;
      Bcount++;
      flag = true;
    }
    cond.notify_one();
  }
}

int main() {
  thread tA(printA);
  thread tB(printB);
  tA.join();
  tB.join();
  return 0;
}