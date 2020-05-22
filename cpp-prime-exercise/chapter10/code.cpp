#include <numeric>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iterator>

using namespace std::placeholders;

void exc_10_3()
{
    std::cout << "Exercise 10.3" << std::endl;
    std::vector<int> v(10, 7);
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << sum << std::endl;
}

void exc_10_4()
{
    std::cout << "Exercise 10.4" << std::endl;
    std::vector<double> v(10, 1.2);
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << sum << std::endl; // result sum = 10
}

void exc_10_6()
{
    std::cout << "Exercise 10.6" << std::endl;
    std::vector<int> a(10, 1);
    std::fill_n(a.begin(), 10, 4);
    for (auto item : a)
        std::cout << item << " ";
    std::cout << std::endl;
}

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

int isShorter(const std::string s1, const std::string s2)
{
    return s1.size() < s2.size();
}

void exc_10_11()
{
    std::cout << "Exercise 10.6" << std::endl;
    std::vector<std::string> words{"the", "quick", "red", "fox", "jumps",
                                   "over", "the", "slow", "red", "turtle"};
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    for (const auto &s : words)
        std::cout << s << " ";
    std::cout << std::endl;
}

bool more_than_five(const std::string &s)
{
    return s.size() > 5;
}

void exc_10_13()
{
    std::cout << "Exercise 10.13" << std::endl;
    std::vector<std::string> words{"the", "quick", "red", "fox", "jumps",
                                   "over", "the", "slow", "red", "turtle"};
    auto end = std::partition(words.begin(), words.end(), more_than_five);
    for (auto it = words.cbegin(); it != end; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void exc_10_20()
{
    std::cout << "Exercise 10.20" << std::endl;
    std::vector<std::string> words{"a", "aa", "aaa", "aaaa", "aaaaaaaa"};
    auto number = std::count_if(words.begin(), words.end(), [](std::string s) -> bool { return s.size() > 6; });
    std::cout << number << std::endl;
}

bool isshorted(const std::string word, std::size_t sz)
{
    return word.size() < sz;
}

void exc_10_22()
{
    std::cout << "Exercise 10.20" << std::endl;
    std::vector<std::string> words{"a", "aa", "aaa", "aaaa", "aaaaaaaa"};

    // using namespace std::placeholder
    auto number = std::count_if(words.begin(), words.end(), std::bind(isshorted, _1, 4));
    std::cout << number << std::endl;
}

// my exercise:
// use ref print word

void print(std::ostream &os, std::string &w, std::string split)
{
    os << w << split;
}

void my_exc_1()
{
    std::cout << "My exercise 1" << std::endl;
    std::vector<std::string> words{"a", "aa", "aaa", "aaaa", "aaaaaaaa"};
    std::ostream &os = std::cout;
    std::for_each(words.begin(), words.end(), std::bind(print, ref(os), _1, ", "));
    std::cout << std::endl;
}

void exc_10_27()
{
    std::cout << "Exercise 10.27" << std::endl;
    std::vector<std::string> words{"a", "aa", "aaa", "aaa"};
    std::vector<std::string> list;
    std::ostream &os = std::cout;
    // using namespace std::placeholder
    std::unique_copy(words.begin(), words.end(), std::inserter(list, list.begin()));
    std::for_each(list.begin(), list.end(), std::bind(print, ref(os), _1, " "));
    std::cout << std::endl;
}

void exc_10_29()
{
    std::cout << "Exercise 10.29" << std::endl;

    std::ifstream ifs("./test,txt");
    std::istream_iterator<std::string> in(ifs), eof;
    std::vector<std::string> vec;
    std::copy(in, eof, std::back_inserter(vec));

    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void exc_10_34()
{
    std::cout << "Exercise 10.34" << std::endl;
    std::vector<int> v{1, 2, 3, 4, 5};
    for (auto it = v.rbegin(); it != v.rend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void exc_10_36()
{
    std::cout << "Exercise 10.36" << std::endl;
    std::list<int> l{1, 0, 2, 3, 0, 9};
    auto it = find(l.crbegin(), l.crend(), 0);

    // [it, rend)
    std::cout << std::distance(it, l.crend()) << std::endl;
}

void exc_10_37()
{
    std::cout << "Exercise 10.37" << std::endl;
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> result;
    std::copy(v.cbegin() + 2, v.cbegin() + 7, std::back_inserter(result));

    // [it, rend)
    std::copy(result.cbegin(), result.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    exc_10_3();
    exc_10_4();
    exc_10_6();
    exc_10_11();
    exc_10_13();
    exc_10_20();
    exc_10_22();
    my_exc_1();
    exc_10_27();
    exc_10_29();
    exc_10_34();
    exc_10_36();
    exc_10_37();
    return 0;
}
