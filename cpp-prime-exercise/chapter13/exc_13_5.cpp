#include <iostream>
#include "StrVec.hpp"

void exc_13_39(){
    std::cout <<"Exercise 13.39" << std::endl;
    StrVec test;
    std::string hello("Hello");
    std::string blank(" ");
    std::string world("World!");
    
    // test push back
    test.push_back(hello);
    test.push_back(blank);
    test.push_back(world);
    for (auto iter = test.begin(); iter!= test.end(); iter++)
        std::cout << *iter;
    std::cout << std::endl;

    // test reserve
    std::cout << "Now capacity: " << test.capacity() << std::endl;
    test.reserve(8);
    std::cout << "After reserve capacity: " << test.capacity() << std::endl;

    // test resize
    std::cout << "Now size: " << test.size() << std::endl;
    test.resize(5, " Dman");
    std::cout << "After resize: " << test.size() << std::endl;
    for (auto iter = test.begin(); iter!= test.end(); iter++)
        std::cout << *iter;
    std::cout << std::endl;
}

void exc_13_40(){
    std::cout <<"Exercise 13.39" << std::endl;
    StrVec test({"Hello", " ", "World!"});
    for (auto iter = test.begin(); iter!= test.end(); iter++)
        std::cout << *iter;
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    exc_13_39();
    exc_13_40();
    std::cout << "Finish exercise 13.5" << std::endl;
    return 0;
}
