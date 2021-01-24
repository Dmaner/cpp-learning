/**
 * 策略模式
 * 优点
 * 1.Strategy及其子类为组件提供了一系列可重用的算法，从而可以使得类型在运行时方便地根据需要在各个算法之间进行切换。
 * 2.Strategy模式提供了用条件判断语句以外的另一种选择，消除条件判断语句，就是在解耦合。
 * 含有许多条件判断语句的代码通常都需要Strategy模式。
 * 3.如果Strategy对象没有实例变量，那么各个上下文可以共享同一个Strategy对象，从而节省对象开销
 * - 定义：
 * 定义一系列算法，把它们一个个封装起来，并且使它们可互相替换
 */

#include <iostream>

class Strategy {
 public:
  virtual ~Strategy() {}
  virtual void run() = 0;
};

class Context {
 private:
  Strategy* m_strategy;

 public:
  Context(Strategy* const strategy) : m_strategy(strategy) {}
  ~Context() { delete m_strategy; }

  void run() { m_strategy->run(); }
};

class StrategyA : public Strategy {
 public:
  ~StrategyA() {}
  void run() override { std::cout << "Strategy A" << std::endl; }
};

class StrategyB : public Strategy {
 public:
  ~StrategyB() {}
  void run() override { std::cout << "Strategy B" << std::endl; }
};

int main(int argc, char const *argv[])
{
    Context ca(new StrategyA);
    Context cb(new StrategyB);
    ca.run();
    cb.run();
    return 0;
}
