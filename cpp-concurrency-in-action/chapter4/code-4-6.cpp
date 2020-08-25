  
#include <future>
#include <iostream>
int find_the_answer()
{
    return 42;
}

void do_other_stuff()
{
    std::cout << "Do other stuff" << std::endl;
}

int main()
{
    std::future<int> the_answer=std::async(find_the_answer);
    do_other_stuff();
    std::cout<<"The answer is "<<the_answer.get()<<std::endl;
}