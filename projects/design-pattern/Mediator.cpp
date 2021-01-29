/**
 * 中介者模式
 * - 定义
 * 用一个中介对象来封装(封装变化)一系列的对象交互。
 * 中介者使各对象不需要显式的相互引用(编译时依赖->运行时依赖)，
 * 从而使其耦合松散(管理变化)，并且可以独立地改变它们之间的交互
 */

#include <iostream>
#include <map>

class People;

class Mediator {
 protected:
  std::map<std::string, People*> m;

 public:
  virtual ~Mediator() {}
  virtual void receive(People* people, const std::string& msg) = 0;
  virtual void send() = 0;
};

class People {
 private:
  std::string name;

 public:
  People(const std::string& n) : name(n) {}
  void send(Mediator& m, People* p, const std::string msg) {
    m.receive(p, msg);
  }
  void receive(const std::string& msg) {
    std::cout << name << " receive " << msg << std::endl;
  }
};

class MessageBox : public Mediator {
 public:
  void receive(People* people, const std::string& msg) override {
    m[msg] = people;
  }
  void send() override {
    for (auto entry : m) {
      entry.second->receive(entry.first);
    }
  }
};

int main(int argc, char const* argv[]) {
  People* p = new People("Bob");
  People* p2 = new People("Dman");
  MessageBox b;
  p->send(b, p2, "Hi");
  b.send();
  return 0;
}
