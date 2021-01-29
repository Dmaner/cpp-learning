/**
 * 门面模式
 * - 定义
 * 为子系统中的一组接口提供一个一致(稳定)的界面，Façade模式定义了一个高层接口，这个接口使得这一子系统更加容易使用(复用)
 */

#include <iostream>

class SubSystem1 {
    public:
    void run(){
        std::cout << "System 1" << std::endl;
    }
};

class SubSystem2 {
    public:
    void run()
    {
        std::cout << "System 2"<<std::endl;
    }
};

class SubSystem3 {
    public:
    void run(){
        std::cout << "System 3" << std::endl;
    }
};

class Facade{
    private:
    SubSystem1 s1;
    SubSystem2 s2;
    SubSystem3 s3;
    public:
    Facade () : s1(), s2(),s3() {}
    void Api1() {
        s1.run();
        s2.run();
    }
    void Api2(){
        s3.run();
    }
};


int main(int argc, char const *argv[])
{
    Facade f;
    f.Api1();
    f.Api2();
    return 0;
}
