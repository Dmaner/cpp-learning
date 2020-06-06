#ifndef FOO_H
#define FOO_H

#include <iostream>
#include <vector>
#include <algorithm>

class Foo
{
public:
    Foo sorted() &&;
    Foo sorted() const &;

private:
    std::vector<int> data;
};

Foo Foo::sorted() && {
    std::sort(data.begin(), data.end());
    std::cout << "Using && sort" << std::endl;
    return *this;
}

Foo Foo::sorted() const & {    
    std::cout << "Using const & sort" << std::endl;
    // Foo ret(*this);
    // ret.sorted(); // lvalue will recursion and stack overflow
    // return ret;
    return Foo(*this).sorted();
}

#endif