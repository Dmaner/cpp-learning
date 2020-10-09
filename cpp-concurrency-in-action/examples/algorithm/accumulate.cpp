#include <numeric>
#include <iostream>
#include <vector>
#include <thread>

// 普通的求和算法
template <typename Iterator, typename T>
T usr_accumulate(Iterator first, Iterator last, T init)
{
    return std::accumulate(first, last, init);
}

// 添加thread

// 添加计算块
template <typename Iterator, typename T>
class accumulate_block
{
public:
    void operator()(Iterator first, Iterator last, T &init)
    {
        init = std::accumulate(first, last, init);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    using ul = unsigned long;
    const ul length = std::distance(first, last);
    if (!length)
        return init;
    const ul min_elements_per_thread = 25;
    const ul max_usr_threads = (length + min_elements_per_thread - 1) / min_elements_per_thread;
    const ul max_sys_threads = std::thread::hardware_concurrency();
    // std::cout << "hardware concurrency threads: " << max_usr_threads << std::endl;
    const ul max_threads = std::max(max_sys_threads == 0 ? 2 : max_sys_threads, max_usr_threads);
    const ul block_size = length / max_threads;

    std::vector<std::thread> threads(max_threads - 1); // 最后一个块由主线程处理
    std::vector<T> results(max_threads);
    Iterator block_start = first;
    for (int i = 0; i < max_threads - 1; i++)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    // 计算最后一个块
    accumulate_block<Iterator, T>()(block_start, last, std::ref(results[max_threads - 1]));
    for (auto &entry : threads)
        entry.join();
    return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char const *argv[])
{
    int n = 256;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
        nums[i] = i;
    std::cout << "using normal accumulate\nsum: " << usr_accumulate(nums.begin(), nums.end(), 0) << std::endl;
    std::cout << "using accumulate with threads\nsum: " << parallel_accumulate(nums.begin(), nums.end(), 0) << std::endl;
    return 0;
}
