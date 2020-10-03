#ifndef HEAD_H
#define HEAD_H

#include <memory>
#include <queue>
#include <iostream>
#include <functional>
#include <thread>
#include <atomic>
#include <vector>
#include <future>

// TODO: implment in chapter 9
struct join_threads
{
  join_threads(std::vector<std::thread> &)
  {
  }
};

// TODO: implment in chapter 8
template <typename T>
class thread_safe_queue
{
public:
  bool try_pop(T &);
};

class function_wrapper
{
  struct impl_base
  {
    virtual void call() = 0;
    virtual ~impl_base() {}
  };

  std::unique_ptr<impl_base> impl;
  template <typename F>
  struct impl_type : impl_base
  {
    F f;
    impl_type(F &&f_) : f(std::move(f_)) {}
    void call() { f(); }
  };

public:
  template <typename F>
  function_wrapper(F &&f) : impl(new impl_type<F>(std::move(f)))
  {
  }

  void operator()() { impl->call(); }

  function_wrapper() = default;

  function_wrapper(function_wrapper &&other) : impl(std::move(other.impl))
  {
  }

  function_wrapper &operator=(function_wrapper &&other)
  {
    impl = std::move(other.impl);
    return *this;
  }

  function_wrapper(const function_wrapper &) = delete;
  function_wrapper(function_wrapper &) = delete;
  function_wrapper &operator=(const function_wrapper &) = delete;
};

class work_stealing_queue
{
private:
  typedef function_wrapper data_type;
  std::deque<data_type> the_queue; // 1
  mutable std::mutex the_mutex;

public:
  work_stealing_queue()
  {
  }

  work_stealing_queue(const work_stealing_queue &other) = delete;
  work_stealing_queue &operator=(
      const work_stealing_queue &other) = delete;

  void push(data_type data) // 2
  {
    std::lock_guard<std::mutex> lock(the_mutex);
    the_queue.push_front(std::move(data));
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(the_mutex);
    return the_queue.empty();
  }

  bool try_pop(data_type &res) // 3
  {
    std::lock_guard<std::mutex> lock(the_mutex);
    if (the_queue.empty())
    {
      return false;
    }

    res = std::move(the_queue.front());
    the_queue.pop_front();
    return true;
  }

  bool try_steal(data_type &res) // 4
  {
    std::lock_guard<std::mutex> lock(the_mutex);
    if (the_queue.empty())
    {
      return false;
    }

    res = std::move(the_queue.back());
    the_queue.pop_back();
    return true;
  }
};

#endif