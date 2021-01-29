/**
 * 代理模式
 * - 定义
 * 为其他对象提供一种代理以控制(隔离，使用接口)对这对象的访问
 */

#include <iostream>

class Subject {
 public:
  virtual ~Subject() {}
  virtual void run() = 0;
};

class RealSubject : public Subject {
 public:
  ~RealSubject() {}
  void run() override { std::cout << "Real Subject" << std::endl; }
};

class Proxy : public Subject {
 private:
  Subject* m_subject;

 public:
  Proxy() { m_subject = new RealSubject(); }
  ~Proxy() { delete m_subject; }
  void run() override {
    std::cout << "Show Proxy" << std::endl;
    m_subject->run();
  }
};

int main(int argc, char const* argv[]) {
  Proxy proxy;
  proxy.run();
  return 0;
}
