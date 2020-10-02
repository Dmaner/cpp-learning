#include <thread>
#include <functional>
#include <algorithm>
#include <future>
#include <vector>
#include <iostream>

template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
        return;

    unsigned long const min_per_thread = 25;

    if (length < 2 * min_per_thread)
        std::for_each(first, last, f);
    else
    {
        Iterator const mid_point = first + length / 2;
        std::future<void> first_half = std::async(&parallel_for_each<Iterator, Func>, first, mid_point, f);
        parallel_for_each(mid_point, last, f);
        first_half.get();
    }
}

// test
int main(int argc, char const *argv[])
{
    std::vector<int> test{1, 2, 3, 4};
    parallel_for_each(test.begin(), test.end(), [](int &a) { std::cout << a << " "; });
    return 0;
}
