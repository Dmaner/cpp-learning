/**
 * 观察者模式/事件模式
 * - 定义：
 * 对象间的一种一对多依赖关系，使得每当一个对象状态发生改变时，其相关依赖对象皆得到通知并被自动更新
 * - 举例
 * 订阅者订阅被观察者，被观察者发生改变时，发出消息通知订阅者
 */

#include <iostream>
#include <vector>

class Subject;

class Observer {
 public:
  virtual ~Observer() {}
  virtual int GetState() = 0;
  virtual void Update(Subject* subject) = 0;
};

/* 被观察者 */
class Subject {
 private:
  std::vector<Observer*> m_observers;

 public:
  /* 订阅 */
  void subscribe(Observer* observer) { m_observers.push_back(observer); }
  /* 发布订阅信息 */
  void notify() {
    for (auto observer : m_observers) {
      observer->Update(this);
    }
  }
  virtual int GetState() = 0;
  virtual void SetState(const int state) = 0;
};

class ConcreteSubject : public Subject {
 private:
  int m_state;

 public:
  int GetState() override { return m_state; }
  void SetState(const int state) override { m_state = state; }
};

class ConcreteObserver : public Observer {
 private:
  int m_state;
  std::string m_name;

 public:
  ConcreteObserver(int state, const std::string& name)
      : m_state(state), m_name(name) {}
  ~ConcreteObserver() {}
  int GetState() override { return m_state; }
  void Update(Subject* subject) override {
    m_state += subject->GetState();
    std::cout << "ConCrete Observer " << m_name << " State " << m_state
              << std::endl;
  }
};

int main(int argc, char const* argv[]) {
  Observer* ob1 = new ConcreteObserver(1, "A");
  Observer* ob2 = new ConcreteObserver(2, "B");
  Subject* subject = new ConcreteSubject();

  subject->subscribe(ob1);
  subject->subscribe(ob2);

  std::cout << "Before update" << std::endl;
  std::cout << ob1->GetState() << std::endl;
  std::cout << ob2->GetState() << std::endl;

  subject->SetState(10);
  subject->notify();

  std::cout << "After update" << std::endl;
  std::cout << ob1->GetState() << std::endl;
  std::cout << ob2->GetState() << std::endl;

  return 0;
}
