#include <condition_variable>
#include <memory>
#include <mutex>

using namespace std;

template <typename T>
class thread_safe_queue
{
private:
    // using linked list for base struct of the implementation of thread safe
    // queue
    struct node
    {
        shared_ptr<T> data;
        unique_ptr<T> next;
    };
    // lock head and tail when they is changing
    mutex head_mutex;
    mutex tail_mutex;

    unique_ptr<node> head; // delete when finsh
    node *tail;

    condition_variable data_condition;

private:
    // auxiliary function
    node *get_tail()
    {
        lock_guard<mutex> tail_lock(tail_mutex);
        return tail;
    }

    unique_lock<mutex> wait_for_data()
    {
        // lock head
        unique_lock<mutex> head_lock(head_mutex);
        // check queue if not empty
        data_condition.wait(head_lock, [&] { return head.get() != get_tail(); });
        return move(head_lock);
    }
    unique_ptr<node> pop_head()
    {
        unique_ptr<node> old_head = move(head);
        head = move(old_head->next);
        return old_head;
    }

    // wait data to pop
    unique_ptr<node> wait_pop_head()
    {
        unique_lock<mutex> head_lock(wait_for_data());
        return pop_head();
    }
    unique_ptr<node> wait_pop_head(T &value)
    {
        unique_lock<mutex> head_lock(wait_for_data());
        value = move(*head->data);
        return pop_head();
    }

    // try to pop
    unique_ptr<node> try_pop_head()
    {
        lock_guard<mutex> head_lock(head_mutex);
        if (head.get() == get_tail())
        {
            // if head and tail both point to the dummy node
            // ps. dummy node prevent to head and tail not to point to the same node
            return unique_ptr<node>();
        }
        return pop_head();
    }
    unique_ptr<node> try_pop_head(T &value)
    {
        lock_guard<mutex> head_lock(head_mutex);
        if (head.get() == get_tail())
            return unique_ptr<node>();
        value = move(*head->data);
        return pop_head();
    }

public:
    thread_safe_queue()
        : head(new node), tail(head.get()) {}
    // prevent copying
    thread_safe_queue(cosnt thread_safe_queue &rhs) = delete;
    thread_safe_queue &operator=(const thread_safe_queue &rhs) = delete;

    // pop function
    shared_ptr<T> try_pop();
    bool try_pop(T &value);

    // wait and pop
    shared_ptr<T> wait_and_pop();
    void wait_and_pop(T &value);

    void push(T new_value);
    bool empty();
};

template <typename T>
void thread_safe_queue<T>::push(T new_value)
{
    shared_ptr<T> new_data = make_shared<T>(move(new_value));
    unique_ptr<node> p(new node);
    {
        lock_guard<mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        node *const new_tail = p.get();
        tail->next = move(p);
        tail = new_tail;
    }

    data_condition.notify_one();
}

template <typename T>
shared_ptr<T> thread_safe_queue<T>::wait_and_pop()
{
    unique_ptr<node> const old_head = wait_and_pop();
    return old_head->data;
}

template <typename T>
void thread_safe_queue<T>::wait_and_pop(T &value)
{
    unique_ptr<node> old_head = wait_and_pop(value);
}

template <typename T>
shared_ptr<T> thread_safe_queue<T>::try_pop()
{
    unique_ptr<node> old_head = try_pop_head();
    return old_head ? old_head->data : shared_ptr<T>();
}

template <typename T>
bool thread_safe_queue<T>::try_pop(T &value)
{
    unique_ptr<node> old_head = try_pop_head();
    return old_head;
}

template <typename T>
bool thread_safe_queue<T>::empty()
{
    lock_guard<mutex> head_lock(head_mutex);
    return head.get() == get_tail();
}