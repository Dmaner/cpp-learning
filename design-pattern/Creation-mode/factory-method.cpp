#include <iostream>
#include <string>

using namespace std;

class Product
{
public:
  virtual ~Product() {}
  virtual void GetType() = 0;
};

class Factory
{
public:
  virtual ~Factory() {}
  virtual Product *CreateA() const = 0;
  virtual Product *CreateB() const = 0;
  virtual void RemoveProduct(Product *) = 0;
};

class ProductA : public Product
{
public:
  ~ProductA() {}
  void GetType() { cout << "Type A" << endl; }
};

class ProductB : public Product
{
public:
  ~ProductB() {}
  void GetType() { cout << "Type B" << endl; }
};

class ConcreteFactory : public Factory
{
public:
  ~ConcreteFactory() {}
  Product *CreateA() const { return new ProductA(); }
  Product *CreateB() const { return new ProductB(); }
  void RemoveProduct(Product *p) { delete p; }
};

int main(int argc, char const *argv[])
{
  Factory *factory = new ConcreteFactory();
  Product *p = factory->CreateA();
  p->GetType();
  factory->RemoveProduct(p);
  p = factory->CreateB();
  p->GetType();
  factory->RemoveProduct(p);
  delete factory;
  return 0;
}
