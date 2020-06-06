#include "Hasptr.h"
#include "Message.hpp"
#include <vector>
#include <algorithm>

void exc_13_5()
{
    std::cout << "Exercise 13.5" << std::endl;
    Hasptr hasptr("Hello");
    Hasptr copyptr = hasptr;
}

void exc_13_8()
{
    std::cout << "Exercise 13.8" << std::endl;
    Hasptr hasptr("Hello");
    Hasptr copyptr("world");
    copyptr = hasptr;
}

void exc_13_27()
{
    std::cout << "Exercise 13.27" << std::endl;
    Hasptr_sec ptr("Hello");
    std::cout << "Point count: " << ptr.counts() << std::endl;
    Hasptr_sec copy_ptr(ptr);
    std::cout << "Point count: " << ptr.counts() << std::endl;
    Hasptr_sec copy_copy_ptr = ptr;
    std::cout << "Point count: " << ptr.counts() << std::endl;
}

void exc_13_29()
{
    std::cout << "Exercise 13.29" << std::endl;
    Hasptr p1("p1");
    Hasptr p2("p2");
    swap(p1, p2);
}

bool compare_hasptr(Hasptr &l, Hasptr &r)
{
    return l < r;
}

void exc_13_31()
{
    std::cout << "Exercise 13.31" << std::endl;
    Hasptr a("a");
    Hasptr b("b");
    Hasptr c("c");
    std::vector<Hasptr> v{b, a, c};
    std::sort(v.begin(), v.end());
    std::cout << "After sort: " << std::endl;
    for (auto item : v)
        std::cout << "value: " << item.value() << " ";
    std::cout << std::endl;
}

void exc_13_34(){
    std::cout << "Exercise 13.34" << std::endl;
    Message m1("Hello!");
    Message m2("Dman");
    Folder f1("Test1");
    Folder f2("Test2");

    // Test folder add and remove
    std::cout << "After adding " << std::endl;
    m1.add_folder(f1);
    m1.add_folder(f2);
    m1.show();
    std::cout << "After removing " << std::endl;
    m1.remove(f2);
    m1.show();
    
}

int main(int argc, char const *argv[])
{
    // exc_13_5();
    // exc_13_8();
    // exc_13_27();
    // exc_13_29();
    // exc_13_31();
    exc_13_34();
    return 0;
}
