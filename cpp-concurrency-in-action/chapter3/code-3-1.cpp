#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(value);
}

bool list_contain(int value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value) != some_list.end();
}

int main()
{
    add_to_list(42);
    std::cout<< std::boolalpha <<"contains(1)="<<list_contain(1)<<", contains(42)="<<list_contain(42)<<std::endl;
}