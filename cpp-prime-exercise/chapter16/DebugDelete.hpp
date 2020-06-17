#ifndef DEBUGDELETE_H
#define DEBUGDELETE_H

#include <iostream>

class DeBugDelete
{

public:
    DeBugDelete(std::ostream& s = std::cerr): os(s) {}
    template <typename T> void operator()(T* p){
        os << "Delete pointer" << std::endl;
        delete p;
    }
private:
    std::ostream& os;
};

#endif