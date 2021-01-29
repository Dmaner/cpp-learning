/**
 * 访问者模式
 * - 定义
 * 表示一个作用与某对象结构中的各元素的操作。使得可以在不改变(稳定)各元素的类的前提下定义(扩展) 作用于这些元素的新操作(变化)。
 * - 个人感觉
 * 需要更多代码经验
 */
#include <iostream>

class Element;
class ConcreteElementA;
class ConcreteElementB;

class Visitor
{
public:
  virtual ~Visitor() {}
  
  virtual void visitElementA( ConcreteElementA* const element ) = 0;
  virtual void visitElementB( ConcreteElementB* const element ) = 0;
  // ...
};

class ConcreteVisitor1 : public Visitor
{
public:
  ~ConcreteVisitor1() {}
  
  void visitElementA( ConcreteElementA* const )
  {
    std::cout << "Concrete Visitor 1: Element A visited." << std::endl;
  }
  
  void visitElementB( ConcreteElementB* const )
  {
    std::cout << "Concrete Visitor 1: Element B visited." << std::endl;
  }
  // ...
};

class ConcreteVisitor2 : public Visitor
{
public:
  ~ConcreteVisitor2() {}
  
  void visitElementA( ConcreteElementA* const )
  {
    std::cout << "Concrete Visitor 2: Element A visited." << std::endl;
  }
  
  void visitElementB( ConcreteElementB* const )
  {
    std::cout << "Concrete Visitor 2: Element B visited." << std::endl;
  }
  // ...
};

class Element
{
public:
  virtual ~Element() {}
  
  virtual void accept( Visitor &visitor ) = 0;
  // ...
};

class ConcreteElementA : public Element
{
public:
  ~ConcreteElementA() {}
  
  void accept( Visitor &visitor )
  {
    visitor.visitElementA( this );
  }
  // ...
};

class ConcreteElementB : public Element
{
public:
  ~ConcreteElementB() {}
  
  void accept( Visitor &visitor )
  {
    visitor.visitElementB( this );
  }
  // ...
};


int main()
{
  ConcreteElementA elementA;
  ConcreteElementB elementB;
  
  ConcreteVisitor1 visitor1;
  ConcreteVisitor2 visitor2;
  
  elementA.accept(visitor1);
  elementA.accept(visitor2);
  
  elementB.accept(visitor1);
  elementB.accept(visitor2);
  
  return 0;
}