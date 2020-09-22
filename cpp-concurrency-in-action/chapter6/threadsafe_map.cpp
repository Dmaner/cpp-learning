#include <mutex>
#include <list>
#include <shared_mutex>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Key, typename Value, typename Hash = hash<Key>>
class threadsafe_lookup_table
{
private:
    // definition atrribute of bucket
    class bucket_type
    {
    private:
        typedef pair<Key, Value> bucket_value;
        typedef list<bucket_value> bucket_data;
        typedef typename bucket_data::iterator bucket_iterator;

        // read write lock
        // mutable prevent const from disabling the modification of mutex
        // c++ 14 lib have no shared_mutex so that using shared_time_mutex for substitute
        mutable shared_timed_mutex mutex;
        bucket_data data;

        // get value
        bucket_iterator find_entry(const Key &key) const
        {
            return find_if(data.begin(), data.end(), [&](bucket_value &item) { return item->first == key; });
        }

    public:
        Value get_value(const Key &key, const Value &default_value)
        {
            shared_lock<shared_timed_mutex> reader_lock(mutex);
            bucket_iterator it = find_entry(key);
            return it == data.end() ? default_value : it->second;
        }

        void add_or_update(const Key &key, const Value &value)
        {
            unique_lock<shared_timed_mutex> writer_lock(mutex);
            bucket_iterator it = find_entry(key);
            if (it == data.end())
            {
                data.push_back(bucket_value(key, value));
            }
            else
            {
                it->second = value;
            }
        }

        void remove_value(const Key &key)
        {
            unique_lock<shared_timed_mutex> writer_lock(mutex);
            bucket_iterator it = find_entry(key);
            if (it != data.end())
            {
                data.erase(it);
            }
        }
    };

    vector<unique_ptr<bucket_type>> buckets;
    Hash hasher;
    bucket_type &get_bucket(const Key &key)
    {
        const size_t index = hasher(key) % buckets.size();
        return *buckets[index];
    }

public:
    // initalization
    threadsafe_lookup_table(unsigned buckets_num = 19, const Hash &_hasher = Hash()) : buckets(buckets_num), hasher(_hasher)
    {
        for (int i = 0; i < buckets_num; i++)
        {
            buckets[i].reset(new bucket_type);
        }
    }

    // prevent copying
    threadsafe_lookup_table(const threadsafe_lookup_table &rhs) = delete;
    threadsafe_lookup_table &operator=(const threadsafe_lookup_table &rhs) = delete;

    Value get_value(const Key &key, const Value &default_value = Value()) const
    {
        get_bucket(key).get_value(key, default_value);
    }

    void add_or_update(const Key &key, const Value &value)
    {
        get_bucket(key).add_or_update(key, value);
    }

    void remove_value(const Key &key)
    {
        get_bucket(key).remove_value(key);
    }
};