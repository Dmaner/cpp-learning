#ifndef BLOB_H
#define BLOB_H
#include <iostream>
#include <memory>
#include <vector>
template <typename T>
class BlobPtr;
template <typename T>
class Blob;

template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob {
  friend class BlobPtr<T>;
  friend bool operator==<T>(const Blob<T>&, const Blob<T>&);

 public:
  typedef T value_type;
  typedef typename std::vector<T>::size_type size_type;
  // constructors
  Blob();
  Blob(std::initializer_list<T> il);
  // size
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  // elements
  void push_back(const T& t) { data->push_back(t); }
  void push_back(T&& t) { data->push_back(std::move(t)); }
  void pop_back();

  T& back();
  T& operator[](size_type);

 private:
  std::shared_ptr<std::vector<T>> data;
  void check(size_type, const std::string&) const;
};
// constructors
template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
    : data(std::make_shared<std::vector<T>>(il)) {}
// check index
template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) const {
  if (i >= data->size()) throw std::out_of_range(msg);
}
// add and remove elements
template <typename T>
void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  return data->pop_back();
}
// element access
template <typename T>
T& Blob<T>::back() {
  check(0, "back on empty Blob");
  return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i) {
  check(i, "index out of range");
  return (*data)[i];
}
// relational operators
template <typename T>
inline bool operator==(const Blob<T>& lhs, const Blob<T>& rhs) {
  return *lhs.data == *rhs.data;
}

#endif  // BLOB_H