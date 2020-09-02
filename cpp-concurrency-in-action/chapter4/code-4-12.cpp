#include <algorithm>
#include <future>
#include <iostream>
#include <list>

template <typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  // add first element
  result.splice(result.begin(), input, input.begin());
  T const& pivot = *result.begin();

  // split twopart
  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](T const& t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

  auto new_lower(sequential_quick_sort(std::move(lower_part)));
  auto new_higher(sequential_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower);
  return result;
}


// parallel test
template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());
  T const& pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](T const& t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

  // use async
  std::future<std::list<T> > new_lower(
      std::async(&parallel_quick_sort<T>, std::move(lower_part)));
  auto new_higher(parallel_quick_sort(std::move(input)));
  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());
  return result;
}

int main(int argc, char const* argv[]) {
  std::list<int> list{4, 3, 2};
  //   list = sequential_quick_sort(list);
  list = parallel_quick_sort(list);
  for (auto e : list) std::cout << e << " ";
  return 0;
}
