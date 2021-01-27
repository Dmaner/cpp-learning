/**
 * 修饰模式
 * - 定义
 * 动态（组合）地给一个对象增加一些额外的职责
 * - 使用场景
 * 在不想增加很多子类的情况下扩展类。
 */

#include <iostream>

/* 基本类 */
class Component {
 public:
  virtual ~Component() {}
  virtual void Operation() = 0;
};

class ConcreteComponent : public Component {
 public:
  ~ConcreteComponent() {}
  void Operation() override { std::cout << "Concrete Component" << std::endl; }
};

/* 修饰器 */
class Decorator : public Component {
 private:
  Component* m_component;

 public:
  Decorator(Component* component) : m_component(component) {}
  ~Decorator() {}
  void Operation() override { m_component->Operation(); }
};

class DecoratorA : public Decorator {
 public:
  DecoratorA(Component* component) : Decorator(component) {}
  ~DecoratorA() {}
  void Operation() override {
    Decorator::Operation();
    std::cout << "Decorator A" << std::endl;
  }
};

class DecoratorB : public Decorator {
 public:
  DecoratorB(Component* component) : Decorator(component) {}
  ~DecoratorB() {}
  void Operation() override {
    Decorator::Operation();
    std::cout << "Decorator B" << std::endl;
  }
};

int main(int argc, char const* argv[]) {
  Component* base = new ConcreteComponent();
  Component* decoratorA = new DecoratorA(base);
  Component* decoratorB = new DecoratorB(decoratorA);
  decoratorB->Operation();
  return 0;
}
