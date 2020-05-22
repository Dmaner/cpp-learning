#include<vector>
#include<iostream>
#include<string>

void exercise_9_41(){
    std::cout << "Exercise 9.41" << std::endl;
    std::vector<char> a{'a', 'b'};
    std::string c(a.cbegin(), a.cend());
    std::cout << c << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<int> a;
    for (int i = 0; i < 20; ++i){
        a.push_back(i);
        std::cout << "Capacity : "<< a.capacity() << " Size: "<<a.size() << std::endl;
    }
    std::string as = "aasdasda";
    std::string b = as.substr(0, 20);
    std::cout << b;
    return 0;
}
