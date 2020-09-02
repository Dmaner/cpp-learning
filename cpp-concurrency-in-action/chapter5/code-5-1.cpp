// 自旋锁
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
using namespace std;
class spinlock_mutex
{
    private:
        atomic_flag flag;
    public:
        spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
        void lock()
        {
            while (flag.test_and_set(memory_order_acquire));
        }

        void unlock()
        {
            flag.clear(memory_order_release);
        }
};

spinlock_mutex spinlock;

void fuc(int n)
{
    for (int i = 0; i < 5; i++)
    {
        spinlock.lock();
        cout << "Thread " << n << " print " << i << endl;
        spinlock.unlock();
    }
}

int main(int argc, char const *argv[])
{
    vector<thread> workers;
    for (int i = 0; i < 3; i++) workers.emplace_back(fuc, i);
    for (auto& t: workers) t.join();
    return 0;
}
