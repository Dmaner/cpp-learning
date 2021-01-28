/**
 * 原型模式
 * - 定义
 * 使用原型实例指定创建对象的种类，然后通过深拷贝这些原型来创建新的对象
 */

#include <iostream>

class Prototype {
 public:
  virtual ~Prototype() {}
  virtual Prototype* clone() = 0;
  virtual void run() = 0;
};

class PrototypeA : public Prototype {
 public:
  ~PrototypeA() {}
  Prototype* clone() override { return new PrototypeA(*this); }
  void run() override { std::cout << "Prototype A" << std::endl; }
};

class Client {
 private:
  Prototype* m_prototype;

 public:
  Client(Prototype* prototype) : m_prototype(prototype) {}
  ~Client() { delete m_prototype; }
  void run() {
    Prototype* p = m_prototype->clone();
    p->run();
  }
};

int main(int argc, char const* argv[]) {
  Prototype* a = new PrototypeA();
  Client client(a);
  client.run();
  return 0;
}
