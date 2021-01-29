/**
 * 责任链
 * - 定义
 * 使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。
 * 将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止
 */

#include <iostream>

class Handler {
    private:
    Handler* m_handler;
    public:
    virtual ~Handler() {}
    virtual void SetHandler(Handler* handler){
        m_handler = handler;
    }
    virtual void HandleRequest(int number){
        if (m_handler)
        {
            m_handler->HandleRequest(number);
        }
    }
};

class ConcreteHandlerA : public Handler {
    private:
    int condition;
    public:
    ConcreteHandlerA(int number) : condition(number) {}
    bool CanHandle(int number) {
        return number < condition;
    }
    void HandleRequest(int number) override {
        if (CanHandle(number)) {
            std::cout << "A can handle" << std::endl; 
        }
        else {
            std::cout << "A cannot handle" << std::endl;
            Handler::HandleRequest(number);
        }
    }
};

class ConcreteHandlerB : public Handler {
    private:
    int condition;
    public:
    
    ConcreteHandlerB(int number) : condition(number) {}
    bool CanHandle(int number) {
        return number < condition;
    }
    void HandleRequest(int number) override {
        if (CanHandle(number)) {
            std::cout << "B can handle" << std::endl; 
        }
        else {
            std::cout << "B cannot handle" << std::endl;
            Handler::HandleRequest(number);
        }
    }
};

int main(int argc, char const *argv[])
{
    Handler* ha = new ConcreteHandlerA(1);
    Handler* hb = new ConcreteHandlerB(3);
    ha->SetHandler(hb);
    ha->HandleRequest(2);
    return 0;
}
