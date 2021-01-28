/**
 * 工厂模式
 * - 定义
 * 定义一个创建对象的接口，让其子类自己决定实例化哪一个工厂类，工厂模式使其创建过程延迟到子类进行
 * - 应用场景
 * 设计一个连接服务器的框架，需要三个协议，"POP3"、"IMAP"、"HTTP"，可以把这三个作为产品类，共同实现一个接口
 */

#include <iostream>

/* 产品基类 */
class Product {
 public:
  virtual ~Product() {}
  virtual void GetName() = 0;
};

/* 工厂基类 */
class Creator {
 public:
  virtual ~Creator() {}
  virtual Product* FactoryMethod() = 0;
};

class ProductA : public Product {
 public:
  ~ProductA() {}
  void GetName() override { std::cout << "Product A" << std::endl; }
};

class ProductB : public Product {
 public:
  ~ProductB() {}
  void GetName() override { std::cout << "Product B" << std::endl; }
};

class ConcreteCreatorA : public Creator {
 public:
  Product* FactoryMethod() override { return new ProductA(); }
};

class ConcreteCreatorB : public Creator {
 public:
  Product* FactoryMethod() override { return new ProductB(); }
};

int main(int argc, char const *argv[])
{
    Creator* ca = new ConcreteCreatorA();
    Creator* cb = new ConcreteCreatorB();
    Product* a = ca->FactoryMethod();
    Product* b = cb->FactoryMethod();
    a->GetName();
    b->GetName();
    return 0;
}
