# C++ 常见面试问题

## 单例模式的实现

- 懒汉版: 延迟初始化

```c++
class Singleton
{
private:
	Singleton() { };
	~Singleton() { };
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
public:
	static Singleton& getInstance() 
    {
		static Singleton instance;
		return instance;
	}
};
```

- 饿汉版：指单例实例在程序运行时被立即执行初始化

```c++
class Singleton
{
private:
	static Singleton instance;
private:
	Singleton();
	~Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
public:
	static Singleton& getInstance() {
		return instance;
	}
}

// initialize defaultly
Singleton Singleton::instance;
```

- 生产者消费者

```c++
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

using namespace std;

mutex cout_mutex;

class BlockQueue
{
  private:
    list<int> msg;
    int cap;
    std::mutex m_mutex;
    std::condition_variable m_con;

  public:
    BlockQueue(int capacity) : cap(capacity)
    {
    }

    bool isFull()
    {
        return msg.size() == cap;
    }

    bool isEmpty()
    {
        return msg.size() == 0;
    }

    void enqueue(int x)
    {
        unique_lock<std::mutex> locker(m_mutex);
        m_con.wait(locker, [this] { return !isFull(); });
        msg.push_back(x);
        m_con.notify_all();
    }
    int dequeue()
    {
        unique_lock<std::mutex> locker(m_mutex);
        m_con.wait(locker, [this] { return !isEmpty(); });
        int ret = msg.front();
        msg.pop_front();
        m_con.notify_all();
        return ret;
    }
};

class Producer
{
  private:
    BlockQueue &buf;

  public:
    Producer(BlockQueue& buffer): buf(buffer) {}
    void run(){
        for (int i = 0; i < 10; i++)
        {
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "Produced: " << i << endl;
            }
            buf.enqueue(i);
        }
    }
};

class Consumer{
private:
    BlockQueue& buf;
public:
    Consumer(BlockQueue& buffer) : buf(buffer){}
    void run(){
        for (int i = 0; i < 10; i++)
        {
            int x = buf.dequeue();
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "Consumer: " << x << endl;
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    BlockQueue que(5);
    Producer p(que);
    Consumer c(que);
    thread p_thread(&Producer::run, &p);
    thread c_thread(&Consumer::run, &c);
    p_thread.join();
    c_thread.join();
    return 0;
}
```

- c++大小端判断

```c++

void IsBigEndian()//原理：联合体union的存放顺序是所有成员都从低地址开始存放，而且所有成员共享存储空间
{
	union temp
	{
		short int a;
		char b;
	}temp;
	temp.a = 0x1234;
	if( temp.b == 0x12 )//低字节存的是数据的高字节数据
	{
		cout << "Big-endian" << endl
	}
	else
	{
		cout << "Little-endian" << endl
	}
}
```