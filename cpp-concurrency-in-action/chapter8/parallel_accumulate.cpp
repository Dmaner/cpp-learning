#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <future>

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last); // 1
    unsigned long const max_chunk_size = 25;
    if (length <= max_chunk_size)
    {
        return std::accumulate(first, last, init); // 2
    }
    else
    {
        Iterator mid_point = first;
        std::advance(mid_point, length / 2); // 3
        std::future<T> first_half_result =
            std::async(parallel_accumulate<Iterator, T>, // 4
                       first, mid_point, init);
        T second_half_result = parallel_accumulate(mid_point, last, T()); // 5
        return first_half_result.get() + second_half_result;              // 6
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    std::vector<int> test;
    int ans = 0;
    int result = 0;
    for (int i = 1; i <= 100; i++)
    {
        test.push_back(i);
        ans += i;
    }
    result = parallel_accumulate(test.begin(), test.end(), 0);
    std::cout << "Answers: " << ans << std::endl;
    std::cout << "Result: " << result << std::endl;
    return 0;
}
