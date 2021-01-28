/**
 * 抽象工厂模式
 * - 定义
 * 提供一个接口，让该接口负责创建一系列”相关或者相互依赖的对象“，无需指定它们具体的类
 */

#include <iostream>

class ProductA {
 public:
  virtual ~ProductA() {}

  virtual const char *getName() = 0;
};

class ConcreteProductAX : public ProductA {
 public:
  ~ConcreteProductAX() {}

  const char *getName() { return "A-X"; }
};

class ConcreteProductAY : public ProductA {
 public:
  ~ConcreteProductAY() {}

  const char *getName() { return "A-Y"; }
};

class ProductB {
 public:
  virtual ~ProductB() {}

  virtual const char *getName() = 0;
};

class ConcreteProductBX : public ProductB {
 public:
  ~ConcreteProductBX() {}

  const char *getName() { return "B-X"; }
};

class ConcreteProductBY : public ProductB {
 public:
  ~ConcreteProductBY() {}

  const char *getName() { return "B-Y"; }
};

class AbstractFactory {
 public:
  virtual ~AbstractFactory() {}

  virtual ProductA *createProductA() = 0;
  virtual ProductB *createProductB() = 0;
};

class ConcreteFactoryX : public AbstractFactory {
 public:
  ~ConcreteFactoryX() {}

  ProductA *createProductA() { return new ConcreteProductAX(); }
  ProductB *createProductB() { return new ConcreteProductBX(); }
};

class ConcreteFactoryY : public AbstractFactory {
 public:
  ~ConcreteFactoryY() {}

  ProductA *createProductA() { return new ConcreteProductAY(); }
  ProductB *createProductB() { return new ConcreteProductBY(); }
};

int main() {
  ConcreteFactoryX *factoryX = new ConcreteFactoryX();
  ConcreteFactoryY *factoryY = new ConcreteFactoryY();

  ProductA *p1 = factoryX->createProductA();
  std::cout << "Product: " << p1->getName() << std::endl;

  ProductA *p2 = factoryY->createProductA();
  std::cout << "Product: " << p2->getName() << std::endl;

  delete p1;
  delete p2;

  delete factoryX;
  delete factoryY;

  return 0;
}