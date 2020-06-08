#include "exc_14_34.hpp"
#include "PrintString.hpp"
#include <algorithm>
#include <vector>
#include <fstream>
#include <functional>
#include <map>

void exc_14_34()
{
    std::cout << "Exercise 14.34" << std::endl;
    IF_THEN_ELSE test;
    test(0, 2, 3);
    test(2, 2, 3);
}

void exc_14_36()
{
    std::cout << "Exercise 14.36" << std::endl;
    std::fstream ifs("./test-14-36.txt");
    std::string s;
    std::vector<std::string> v;
    while (std::getline(ifs, s))
        v.push_back(s);
    std::for_each(v.begin(), v.end(), PrintString(std::cout, " end \n"));
}

void exc_14_42(){

    std::cout << "Exercise 14.42" << std::endl;
    using std::placeholders::_1;

    std::vector<int> ivec { 1, 111, 1111, 11111 };
    int count = std::count_if (ivec.cbegin(), ivec.cend(), std::bind(std::greater<int>(), _1, 1024));
    std::cout << count << std::endl;

    std::vector<std::string> svec { "pooh", "pooh", "pezy", "pooh" };
    auto found = std::find_if (svec.cbegin(), svec.cend(), std::bind(std::not_equal_to<std::string>(), _1, "pooh"));
    std::cout << *found << std::endl;

    std::transform(ivec.begin(), ivec.end(), ivec.begin(), std::bind(std::multiplies<int>(), _1, 2));
    for (int i : ivec) std::cout << i << " ";
    std::cout << std::endl;
}

int add(int a, int b)
{
    return a + b;
}

struct divide
{
    int operator() (int a, int b){
        return a / b;
    } 
};

void exc_14_44()
{
    std::cout << "Exercise 14.44" << std::endl;
    auto mod = [](int a, int b) { return a % b;};
    std::map<std::string, std::function<int(int, int)>> binops;
    binops["+"] = add;
    binops["-"] = std::minus<int>();
    binops["/"] = divide();
    binops["*"] = [](int a, int b) {return a *b;};
    binops["%"] = mod;
    std::cout << "10 + 5 = " << binops["+"](10, 5) << std::endl;
    std::cout << "10 - 5 = " << binops["-"](10, 5) << std::endl;
    std::cout << "10 / 5 = " << binops["/"](10, 5) << std::endl;
    std::cout << "10 * 5 = " << binops["*"](10, 5) << std::endl;
    std::cout << "10 % 5 = " << binops["%"](10, 5) << std::endl;
    
}

int main()
{
    exc_14_34();
    exc_14_36();
    exc_14_42();
    exc_14_44();
    return 0;
}