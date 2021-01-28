/**
 * 建造者模式
 * - 定义
 * 将一个复杂对象的构建与其表示相分离，使得同样的构建过程(稳定)可以创建不同的表示(变化)
 */

#include <iostream>

/* 对象基类 */
class Product {
 public:
  virtual ~Product() {}
  virtual void AddPart(const std::string& part) = 0;
  virtual void Show() = 0;

 protected:
  std::string m_shape;
};

class Builder {
 protected:
  Product* m_product;

 public:
  Builder(Product* product) : m_product(product) {}
  virtual ~Builder() { delete m_product; }
  virtual void First() = 0;
  virtual void Second() = 0;
  virtual Product* GetProduct() = 0;
};

/* 总体构建方法基类 */
class Director {
 protected:
  Builder* m_builder;

 public:
  Director(Builder* builder) : m_builder(builder) {}
  virtual ~Director() { delete m_builder; }
  virtual void build() = 0;
  virtual Product* GetProduct() = 0;
};

/* 实现类 */
class ProductA : public Product {
 public:
  void AddPart(const std::string& s) override { m_shape += s; }
  void Show() override { std::cout << m_shape << std::endl; }
};

class BuilderA : public Builder {
 public:
  BuilderA(Product* product) : Builder(product) {}
  void First() override { m_product->AddPart(" A "); }
  void Second() override { m_product->AddPart(" B "); }
  Product* GetProduct() override { return m_product; }
};

class DirectorA : public Director {
 public:
  DirectorA(Builder* builder) : Director(builder) {}
  void build() override {
    m_builder->First();
    m_builder->Second();
  }
  Product* GetProduct() { return m_builder->GetProduct(); }
};

int main(int argc, char const* argv[]) {
  Product* p = new ProductA();
  Builder* builder = new BuilderA(p);
  Director* director = new DirectorA(builder);
  director->build();
  p = director->GetProduct();
  p->Show();

  return 0;
}
