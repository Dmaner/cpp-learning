#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class Producer_Consumer
{
    private:
        size_t begin;
        size_t end;
        size_t cur;
        vector<int> buffer;
        condition_variable not_full;
        condition_variable not_empty;
        mutex mut;
    public:
        // prevent copying
        Producer_Consumer(const Producer_Consumer& rhs) = delete;
        Producer_Consumer& operator=(const Producer_Consumer& rhs) = delete;

        // init
        Producer_Consumer(size_t sz): begin(0), end(0), cur(0), buffer(sz) {}

        void Produce(int n) 
        {
            {
                unique_lock<mutex> lock(mut);
                
                not_full.wait(lock, [=]{return cur < buffer.size();});

                // add new
                buffer[end] = n;
                end = (end + 1) % buffer.size();
                ++ cur;
            }
            not_empty.notify_one();
        }

        int Comsume()
        {
            unique_lock<mutex> lock(mut);
            not_empty.wait(lock, [=]{return cur > 0;});
            int n = buffer[begin];
            begin = (begin + 1) % buffer.size();
            -- cur;
            lock.unlock();
            not_full.notify_one();
            return n;
        }
};

Producer_Consumer buffers(2);
mutex io_mutex;

void Producer()
{
    int n = 0;
    while (n < 10)
    {
        buffers.Produce(n);
        unique_lock<mutex> lock(io_mutex);
        cout << "Produce --- " << n << endl; 
        lock.unlock();
        n++;
    }

    // maker other comsumer delete
    buffers.Produce(-1);
}

void Comsumer()
{
    thread::id thread_id = this_thread::get_id();
    int n = 0;
    do
    {
        n = buffers.Comsume();
        unique_lock<mutex> lock(io_mutex);
        cout << "Comsume --- " << n << endl; 
        lock.unlock();
    } while (n != -1);
    buffers.Produce(-1);
}

int main(int argc, char const *argv[])
{
    vector<thread> threads;
    threads.push_back(thread(&Producer));
    threads.push_back(thread(&Comsumer));
    threads.push_back(thread(&Comsumer));
    threads.push_back(thread(&Comsumer));

    for (auto & t : threads)
    {
        t.join();
    }

    return 0;
}
