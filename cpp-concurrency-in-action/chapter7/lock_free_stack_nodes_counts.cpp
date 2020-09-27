#include <memory>
#include <atomic>

using namespace std;

template <typename T>

class lock_free_stack
{
private:
    struct node;

    struct counted_node_ptr
    {
        int external_count;
        node *ptr;
    };

    struct node
    {
        shared_ptr<T> data;
        atomic<int> internal_counts;
        counted_node_ptr *next;

        node(const T &data_) : data(data_), internal_counts(0) {}
    };

    atomic<counted_node_ptr> head;
    // find the head with one thread acessing
    void increase_head_count(counted_node_ptr &old_counter)
    {
        counted_node_ptr new_counter;
        do
        {
            new_counter = old_counter;
            ++new_counter.external_count;
        } while (!head.compare_exchange_strong(old_counter, new_counter,
                                               memory_order_acquire, memory_order_relaxed));

        old_counter.external_count = new_counter.external_count;
    }

public:
    shared_ptr<T> pop();
    void push(const T &data);
    ~lock_free_stack()
    {
        while (pop())
            ;
    }
};

template <typename T>
void lock_free_stack<T>::push(const T &data)
{
    counted_node_ptr new_node;
    new_node.ptr = new node(data);
    // add a reference to new node by the head pointer
    new_node.external_count = 1;
    new_node.ptr->next = head.load(memory_order_relaxed);

    // you need a release operation to get a happensbefore relationship between threads
    while (!head.compare_exchange_weak(new_node.ptr->next, new_node,
                                       memory_order_release, memory_order_acquire))
        ;
}

template <typename T>
shared_ptr<T> lock_free_stack<T>::pop()
{
    counted_node_ptr old_head = head.load(memory_order_relaxed);
    while (true)
    {
        increase_head_count(old_head);
        node *const ptr = old_head.ptr;
        if (!ptr)
        {
            return shared_ptr<T>();
        }
        // if not empty delete
        if (head.compare_exchange_strong(old_head, ptr->next, memory_order_relaxed))
        {
            shared_ptr<T> res;
            res.swap(ptr->data);
            const int count_increase = old_head.external_count - 2;
            // if count_increase + internal_counts = 0 fetch_add's return value == - count_increase
            if (ptr->internal_counts.fetch_add(count_increase,
                                               memory_order_release) == -count_increase)
                delete ptr;

            return res;
        }
        else if (ptr->internal_counts.fetch_sub(1, memory_order_relaxed) == 1)
        {
            ptr->internal_counts.load(memory_order_acquire);
            delete ptr;
        }
    }
}