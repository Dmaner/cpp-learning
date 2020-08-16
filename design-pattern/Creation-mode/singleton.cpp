#include <atomic>
#include <mutex>

using namespace std;

// 饿汉
class singleton {
 private:
  static singleton* p;
  singleton() {}

 public:
  static singleton* instance();
};

singleton* singleton::instance() {
  if (p == nullptr) {
    p = new singleton();
  }
  return p;
}

// 饿汉

class singleton2 {
 private:
  static singleton2* p;
  singleton2() {}

 public:
  static singleton2* instance();
};

singleton2* singleton2::p = new singleton2();

singleton2* singleton2::instance() { return p; }

// besr of all in c++11

class singleton_th {
 private:
  singleton_th() {}
  ~singleton_th() {}
  singleton_th(const singleton_th&);
  singleton_th& operator=(const singleton_th&);

 public:
  static singleton_th& instance();
};

singleton_th& singleton_th::instance() {
  static singleton_th inst;
  return inst;
}
