#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

std::mutex cout_mutex;

// 缓冲区
class Buffer {
 private:
  std::deque<int> products;
  std::mutex mutex;
  std::condition_variable cond;
  unsigned int max_num;

 public:
  Buffer(unsigned int num) : max_num(num) {}
  void add(int num) {
    while (true) {
      std::unique_lock<std::mutex> lock(mutex);

      // 直到缓冲区满
      cond.wait(lock, [this] { return products.size() < max_num; });
      products.push_back(num);
      lock.unlock();
      cond.notify_all();
      break;
    }
  }
  int remove() {
    while (true) {
      std::unique_lock<std::mutex> lock(mutex);

      // 直到缓冲区不为空
      cond.wait(lock, [this] { return products.size() > 0; });
      int element = products.front();
      products.pop_front();
      lock.unlock();
      cond.notify_all();
      return element;
    }
  }
};

class Producer {
 private:
  Buffer &buf;

 public:
  Producer(Buffer &buffer) : buf(buffer) {}
  void run() {
    thread_local std::random_device rd;
    thread_local std::mt19937 engine(rd());
    thread_local std::uniform_int_distribution<int> dist(0, 99);

    while (true) {
      int num = dist(engine);
      {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Produced: " << num << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
      buf.add(num);
    }
  }
};

class Consumer {
 private:
  Buffer &buf;

 public:
  Consumer(Buffer &buffer) : buf(buffer) {}
  void run() {
    while (true) {
      int num = buf.remove();
      {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Consumer: " << num << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
    }
  }
};

int main(int argc, char const *argv[]) {
  Buffer b(10);

  Producer p(b);
  Consumer c(b);

  std::thread p_thread(&Producer::run, &p);
  std::thread c_thread(&Consumer::run, &c);

  p_thread.join();
  c_thread.join();

  return 0;
}
