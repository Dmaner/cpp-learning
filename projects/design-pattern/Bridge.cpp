/**
 * 桥接模式
 * - 定义
 * 将抽象部分(业务功能)与实现部分(平台实现)分离，使它们都可以独立地变化
 * - 应用场景
 * 实现系统可能有多个角度分类，每一种角度都可能变化
 */
#include <iostream>

/* 平台实现 */
class Implementor {
 public:
  virtual ~Implementor() {}
  virtual void action() = 0;
};

class ImplementorA : public Implementor {
 public:
  ~ImplementorA() {}
  void action() override { std::cout << "A implementor" << std::endl; }
};

class ImplementorB : public Implementor {
 public:
  ~ImplementorB() {}
  void action() override { std::cout << "B implementor" << std::endl; }
};

/* 业务功能 */
class Abstraction {
 public:
  virtual ~Abstraction() {}
  virtual void action() = 0;
};

/* 修正业务功能 */
class RefinedAbstraction : public Abstraction {
 private:
  Implementor* m_implementor;

 public:
  RefinedAbstraction(Implementor* implementor) : m_implementor(implementor) {}
  ~RefinedAbstraction() {}
  void action() override {
      m_implementor->action();
  }
};

int main(int argc, char const *argv[])
{
    Implementor* impA = new ImplementorA();
    Implementor* impB = new ImplementorB();
    Abstraction* abs = new RefinedAbstraction(impA);
    abs->action();
    abs = new RefinedAbstraction(impB);
    abs->action();
    return 0;
}
