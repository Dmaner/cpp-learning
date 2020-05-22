#include<iostream>
#include<vector>

int exercise_6_55(int , int);

int reset(int &a){
    a ++;
    return a;
}

int reset(int* a){
    a++;
    return *a;
}

void print(const int ia[2])
{
	for (size_t i = 0; i != 2; ++i)
		std::cout << ia[i] << std::endl;
}

void exercise_6_27(std::initializer_list<int> li){
    int sum = 0;
    for (const auto &t: li){
        sum += t;
    }
    std::cout << sum << std::endl;
}

int main(int argc, char const *argv[])
{
    int b = 1;
    int const *a = &b;
    int c[2] = {1,2};
    std::cout << reset(b) << std::endl;
    std::cout << reset(b) << std::endl;
    std::vector<decltype(exercise_6_55) * > test;
    print(c);
    auto d = {10, 20 , 30 ,10};
    exercise_6_27(d);
    return 0;
}
