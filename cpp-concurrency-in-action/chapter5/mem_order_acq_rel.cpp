#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

atomic<int> data[2];
atomic<int> sync(0);

void thread_1()
{
    data[0].store(42, memory_order_relaxed);
    data[1].store(31, memory_order_relaxed);
    sync.store(1, memory_order_release);
    cout << "Sync load 1 ...\n";
}

void thread_2()
{
    int expected = 1;
    while (!sync.compare_exchange_strong(expected, 2, memory_order_acq_rel)) {
        expected = 1;
        cout << "Load failed ...\n";
        }
    cout << "Sync load 2 ...\n";
}

void thread_3()
{
    while (sync.load(memory_order_acquire) < 2);
    assert(data[0].load(memory_order_relaxed) == 42);
    assert(data[1].load(memory_order_relaxed) == 31);
    cout << "Pass test.\n";
}

int main(int argc, char const *argv[])
{
    thread t1(thread_1), t2(thread_2), t3(thread_3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
