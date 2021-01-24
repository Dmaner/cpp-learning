/**
 * 模板模式：
 * - 应用场景：
 * 在软件构建过程中，对于某一项任务，它常常有稳定的整体操作结构，但各个子步骤却有很多改变的需求，
 * 或者由于固有的原因（比如框架与应用之间的关系）而无法和任务的整体结构同时实现。
 * - 定义：
 * 定义一个操作中的算法的骨架，而将一些步骤延迟到子类中
 */

#include <iostream>

/* 一个算法框架，将具体步骤的实现延迟到子类 */
class AlgorithmFrame {
 public:
  virtual ~AlgorithmFrame() {}

  void run() {
    FirstStep();
    SecondStep();
  }

  virtual void FirstStep() = 0;
  virtual void SecondStep() = 0;
};

class ConcreteClass : public AlgorithmFrame {
 public:
  ~ConcreteClass(){};

  void FirstStep() override { std::cout << "First Step" << std::endl; }
  void SecondStep() override { std::cout << "Second Step" << std::endl; }
};

int main(int argc, char const* argv[]) {
  AlgorithmFrame* item = new ConcreteClass();
  item->run();
  delete item;
  return 0;
}
