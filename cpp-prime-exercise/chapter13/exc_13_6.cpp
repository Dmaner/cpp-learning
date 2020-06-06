#include "StrVec.hpp"
#include "Foo.hpp"

void exc_13_50(){
    std::cout << "Exercise 13.50" << std::endl;
    std::string a("a");
    std::string b("b");
    StrVec v;
    v.push_back(a);
    StrVec v_copy(v);
    StrVec v_move_copy(std::move(v));
}

void exc_13_58(){
    std::cout << "Exercise 13.58" << std::endl;
    Foo().sorted();
    Foo f;
    f.sorted();
}

int main(int argc, char const *argv[])
{
    exc_13_50();
    exc_13_58();
    return 0;
}
