#include <functional>
#include <iostream>
#include <list>
#include <vector>

#include "Blob.hpp"
#include "BlobPtr.hpp"
#include "DebugDelete.hpp"

template <typename T>
bool compare(const T& p, const T& q) {
  if (std::less<T>()(p, q))
    return true;
  else
    return false;
}

template <typename Iterator, typename Value>
Iterator find(Iterator begin, Iterator end, Value value) {
  for (; begin != end && *begin != value; begin++)
    ;
  return begin;
}
/*
this template only fit simple array

template<typename T, unsigned N>
void print(T (&arr)[N])
{
    for (unsigned i = 0; i < N; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

*/

template <typename T>
void print(T const& vec) {
  for (auto const& item : vec) std::cout << item << "\t";
  std::cout << std::endl;
}

template <typename T, unsigned size>
T* begin(T (&arr)[size]) {
  return arr;
}

template <typename T, unsigned size>
T* end(T (&arr)[size]) {
  return arr + size;
}

void exc_16_2() {
  std::cout << "Exercise 16.2\n";
  std::cout << "Compare (2, 3) = " << compare(2, 3) << std::endl;
  std::cout << "Compare (0.1, 0.3) = " << compare(0.1, 0.3) << std::endl;
}

void exc_16_4() {
  std::cout << "Exercise 16.4\n";
  std::vector<int> a{1, 2, 3, 4, 5};
  std::string ans =
      find(a.cbegin(), a.cend(), 2) == a.cend() ? "False" : "True";
  std::cout << ans << std::endl;
  std::list<std::string> b{"a", "b", "c"};
  ans = find(b.cbegin(), b.cend(), "d") == b.cend() ? "False" : "True";
  std::cout << ans << std::endl;
}

void exc_16_5() {
  std::cout << "Exercise 16.5\n";
  std::string a[] = {"a", "b"};
  char b[] = {'c', 'd'};
  std::vector<int> c = {1, 2, 3};
  print(a);
  print(b);
  print(c);
}

void exc_16_6() {
  std::cout << "Exercise 16.6\n";
  std::vector<std::string> v{"abc", "bca"};
  std::cout << *(begin(v)) << std::endl;
  std::cout << *(end(v) - 1) << std::endl;
}

void exc_16_12() {
  std::cout << "Exercise 16.12\n";
  Blob<std::string> blob;
  blob.push_back("abc");
  blob.push_back("efg");
  std::cout << "Back: " << blob.back() << std::endl;
  std::cout << "Size: " << blob.size() << std::endl;
  BlobPtr<std::string> ptr(blob);
  std::cout << "Curr 0: " << ptr[0] << std::endl;
  std::cout << "Curr 1: " << ptr[1] << std::endl;
  ptr++;
  std::cout << "Curr now: " << *(ptr) << std::endl;
}

template <typename Container>
void fuc_16_19(Container& vec) {
  for (typename Container::size_type i = 0; i < vec.size(); i++)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
}

template <typename Container>
void fuc_16_20(Container& vec) {
  for (typename Container::const_iterator begin = vec.cbegin();
       begin != vec.cend(); begin++)
    std::cout << *begin << " ";
  std::cout << std::endl;
}

void exc_16_19() {
  std::cout << "Exercise 16.19\n";
  std::vector<int> a{1, 2, 3};
  fuc_16_19<std::vector<int>>(a);
}

void exc_16_20() {
  std::cout << "Exercise 16.20\n";
  std::vector<int> a{1, 2, 3};
  fuc_16_19<std::vector<int>>(a);
}

void exc_16_21()
{
  std::cout << "Exercise 16.21\n";
  DeBugDelete d(std::cout);
  int *p = new int;
  double *p2 = new double;
  d(p);
  d(p2);
}

int main(int argc, char const* argv[]) {
  exc_16_2();
  exc_16_4();
  exc_16_5();
  exc_16_6();
  exc_16_12();
  exc_16_19();
  exc_16_20();
  exc_16_21();
  return 0;
}
