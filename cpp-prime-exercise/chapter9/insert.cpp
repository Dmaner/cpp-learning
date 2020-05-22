#include<iostream>
#include<vector>

int main(int argc, char const *argv[])
{
    std::vector<int> a{1,4,3};
    auto iter = a.begin() + 1;
    iter = a.insert(iter, 10, 2);
    std::cout << *(iter-1) << std::endl;
    for (auto num: a){
        std::cout << num << " ";
    }
    return 0;
}
