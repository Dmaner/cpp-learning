#ifndef EXC_14_34_H
#define EXC_14_34_H

#include <iostream>

class IF_THEN_ELSE
{
public:
    void operator()(int a, int b, int c)
    {
        if (check(a)) std::cout << b << std::endl;
        else std::cout << c << std::endl;
    }

private:
    bool check(int arg) { return arg == 0; }
};

#endif