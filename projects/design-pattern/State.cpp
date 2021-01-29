/**
 * 状态模式
 * - 定义
 * 允许一个对象在其内部状态改变时改变它的行为。从而使对象看起来似乎修改了其行为
 */

#include <iostream>

class State {
    public:
    virtual ~State() {}
    virtual void run() = 0;
};

class ConcreteStateA : public State {
    public:
    ~ConcreteStateA () {}
    void run() override {
        std::cout << "State A" << std::endl;
    }
};

class ConcreteStateB: public State {
    public:
    ~ConcreteStateB() {}
    void run() override {
        std::cout << "State B" << std::endl;
    }
};

class Context {
    private:
    State * m_state;
    public:
    void SetState(State* state){
        m_state = state;
    }
    void run() {
        m_state->run();
    }
};


int main(int argc, char const *argv[])
{
    State* sa = new ConcreteStateA();
    State* sb = new ConcreteStateB();
    Context context;
    context.SetState(sa);
    context.run();
    context.SetState(sb);
    context.run();
    return 0;
}
