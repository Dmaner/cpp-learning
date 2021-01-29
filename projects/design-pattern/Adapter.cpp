/**
 * 适配器模式
 * - 定义
 * 将一个类的接口转换成客户希望的另一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作
 */

#include <iostream>

//////////////////
//  对象适配器   //
//////////////////

/* 之前的接口 */
class Adaptee {
 public:
  virtual ~Adaptee() {}
  void run() { std::cout << "Adaptee" << std::endl; }
};

/* 目标设计接口 */
class Target {
 public:
  virtual ~Target() {}
  virtual void run() = 0;
};

class Adapter : public Target {
 private:
  Adaptee* adaptee;

 public:
  Adapter() { adaptee = new Adaptee(); }
  void run() override {
    std::cout << "Add something" << std::endl;
    adaptee->run();
  }
};

int main(int argc, char const* argv[]) {
  Adapter* apt = new Adapter();
  apt->run();
  return 0;
}
