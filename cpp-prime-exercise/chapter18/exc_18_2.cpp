#include <iostream>

namespace test1
{
    namespace exercise
    {
        int var = 0;
        double dvar = 0;
        const int limit = 0;
    } // namespace exercise
    int var = 999;
    int number = 1;
    // using exercise::var; wiil causes a multiple declaration
    using exercise::limit;
    using exercise::dvar;
    void mainip(){
        double dvar = 3.14;
        std::cout << "dvar = " <<dvar << std::endl;
        int iobj = limit + 1;
        std::cout << "iobj = " << iobj << std::endl;
        ++var;
        std::cout << "var = " << var << std::endl;
        ++test1::var;
        std::cout << "Test" << number<< "::var = " << test1::var << std::endl;
    }
} // namespace test1 

namespace test2
{
    namespace exercise
    {
        int var = 0;
        double dvar = 0;
        const int limit = 0;
    } // namespace exercise
    int var = 999;
    int number = 2;
    void mainip(){
        using exercise::limit;
        // using exercise::dvar;
        using exercise::var;
        double dvar = 3.14;
        std::cout << "dvar = " <<dvar << std::endl;
        int iobj = limit + 1;
        std::cout << "iobj = " << iobj << std::endl;
        ++var;
        std::cout << "var = " << var << std::endl;
        ++test2::var;
        std::cout << "Test" << number<< "::var = " << test1::var << std::endl;
    }
} // namespace test2



int main(int argc, char const *argv[])
{
    test1::mainip();
    test2::mainip();
    return 0;
}

