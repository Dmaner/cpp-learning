/** 
 * 命令模式
 * - 定义
 * 将一个请求(行为)封装成一个对象，从而使你可用不用的请求对客户进行参数化；
 * 对请求排队或记录请求日志，以及支持可撤销的操作
 * - 个人感觉
 * 相当于写一个shell脚本
 */

#include <iostream>

class Receiver {
    public:
    void action(){
        std::cout << "Receive action" << std::endl;
    }
};

class Command {
    protected:
    /* 防止类外构造 */
    Command() {}
    public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
    private:
    Receiver* m_receiver;
    public:
    ConcreteCommand(Receiver* receiver) : m_receiver(receiver) {}
    ~ConcreteCommand() {
        if (m_receiver) delete m_receiver;
    }
    void execute() override {
        return m_receiver->action();
    }
};

class Invoker {
    private :
    Command* m_cmd;
    public:
    ~Invoker() {
        if (m_cmd) delete m_cmd;
    }
    void GetCMD(Command* cmd) {
        std::cout << "Get CMD" << std::endl;
        m_cmd = cmd;
    }
    void Confirm() {
        std::cout << "Confirm" << std::endl;
        if (m_cmd)
        {
            m_cmd->execute();
        }
    }
};

int main(int argc, char const *argv[])
{
    Receiver* receiver = new Receiver();
    Command* cmd = new ConcreteCommand(receiver);
    Invoker invoker;
    invoker.GetCMD(cmd);
    invoker.Confirm();
    return 0;
}
