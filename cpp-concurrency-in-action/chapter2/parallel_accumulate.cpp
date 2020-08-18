#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

typedef unsigned long const ulc;

template <typename Iterator, typename T>
struct accumulate_block {
  void operator()(Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    ulc length = std::distance(first, last);

    if (length == 0) return init;

    // calulacte the min number of threads
    ulc task_pre_thread = 25;
    ulc max_thread = (length + task_pre_thread - 1) / task_pre_thread;
    
    // get the number of threds that hardware supported
    ulc hardware_threads = std::thread::hardware_concurrency();

    ulc num_of_thread = std::min(hardware_threads == 0 ? 2: hardware_threads, max_thread);
    
    // split set into blocks
    ulc blocks = length / num_of_thread;
    
    std::vector<T> results(num_of_thread);

    // left main thread
    std::vector<std::thread> threads(num_of_thread-1);
    Iterator block_first = first;
    for (unsigned long i = 0; i < num_of_thread - 1; ++i)
    {
        Iterator block_end = block_first;
        threads[i] = std::thread(
            accumulate_block<Iterator, T>(),
            block_first, block_end, std::ref(results[i])
        );
        block_first = block_end;
    } 
    for (std::thread& entry : threads) entry.join();

    // add last block
    accumulate_block<Iterator, T>()(block_first, last, results[num_of_thread-1]);
    return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char const* argv[]) {
  /* code */
  std::vector<int> test;
  int ans = 0;
  int result = 0;
  for (int i = 1; i <= 100; i++) {
    test.push_back(i);
    ans += i;
  }
  result = parallel_accumulate(test.begin(), test.end(), 0);
  std::cout << "Answers: " << ans << std::endl;
  std::cout << "Result: " << result << std::endl;
  return 0;
}
