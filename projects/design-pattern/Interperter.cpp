/**
 * 解析器模式
 * - 定义
 * 给定一个语言，定义它的文法的一种表示，并定义一种解释器，这个解释器使用该表示来解释语言中的句子
 * - 个人感觉
 * 就是类似正则表达式
 */

#include <iostream>
#include <map>

class Context
{
public:
  void set( const std::string& var, const bool value)
  {
    vars.insert( std::pair<std::string, bool>( var, value ) );
  }
  
  bool get( const std::string& exp )
  {
    return vars[ exp ];
  }
  // ...

private:
  std::map<std::string, bool> vars;
  // ...
};


class AbstractExpression
{
public:
  virtual ~AbstractExpression() {}
  
  virtual bool interpret( Context* const )
  {
    return false;
  }
  // ...
};

class TerminalExpression : public AbstractExpression
{
public:
  TerminalExpression( const std::string& val ) : value( val ) {}
  
  ~TerminalExpression() {}
  
  bool interpret( Context* const context )
  {
    return context->get( value );
  }
  // ...
  
private:
  std::string value;
  // ...
};


class NonterminalExpression : public AbstractExpression
{
public:
  NonterminalExpression( AbstractExpression *left, AbstractExpression *right ) : 
    lop( left ), rop( right ) {}
  
  ~NonterminalExpression()
  {
    delete lop;
    delete rop;
  }
  
  bool interpret( Context *const context )
  {
    return lop->interpret( context ) && rop->interpret( context );
  }
  // ...
  
private:
  AbstractExpression *lop;
  AbstractExpression *rop;
  // ...
};


int main()
{
  AbstractExpression *A = new TerminalExpression("A");
  AbstractExpression *B = new TerminalExpression("B");
  AbstractExpression *exp = new NonterminalExpression( A, B );
  
  Context context;
  context.set( "A", true );
  context.set( "B", false );
  
  std::cout << context.get( "A" ) << " AND " << context.get( "B" );
  std::cout << " = " << exp->interpret( &context ) << std::endl;
  
  delete exp;
  return 0;
}

