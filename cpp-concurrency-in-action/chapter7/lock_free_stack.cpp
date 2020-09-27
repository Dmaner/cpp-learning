#include <atomic>
#include <memory>

using namespace std;

template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        shared_ptr<T> data;
        node *next;
        node(const T &val) : data(make_shared<T>(val)) {}
    };

    atomic<node *> head;
    // record pop how many elements
    atomic<unsigned> threads_in_op;
    atomic<node *> to_be_deleted;

    // delete nodes waiting to be deleted
    static void delete_nodes(node *nodes)
    {
        while (nodes)
        {
            node *next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void try_reclaim(node *old_head)
    {
        if (threads_in_op == 1)
        {
            node *nodes_to_delete = to_be_deleted.exchange(nullptr);
            // if only one thread using pop() 
            // then delete all nodes to be deleted
            if (!--threads_in_op)
            {
                delete_nodes(nodes_to_delete);
            }
            else if (nodes_to_delete)
            {
                chain_pending_nodes(nodes_to_delete);
            }
            delete old_head;
        }
        else
        {
            chain_pending_node(old_head);
            --threads_in_op;
        }
    }

    // add delete node
    void chain_pending_nodes(node *nodes)
    {
        node *last = nodes;
        while (node *const next = last->next)
        {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }
    void chain_pending_nodes(node *fisrt, node *last)
    {
        last->next = to_be_deleted;
        while (!to_be_deleted.compare_exchange_weak(last->next, fisrt))
            ;
    }
    void chain_pending_node(node *n)
    {
        chain_pending_nodes(n, n);
    }

public:
    void push(const T &data)
    {
        node *const new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ;
    }

    shared_ptr<T> pop()
    {
        ++threads_in_op;
        node *old_head = head.load();
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next))
            ;
        shared_ptr<T> res;
        if (old_head)
        {
            res.swap(old_head->data);
        }
        try_reclaim(old_head);
        return res;
    }
};