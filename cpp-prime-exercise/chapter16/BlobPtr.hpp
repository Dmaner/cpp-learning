#ifndef BLOBPTR_H
#define BLOBPTR_H

#include "Blob.hpp"

template <typename T>
bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T>
class BlobPtr {
  friend bool operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);
 public:
  typedef typename std::vector<T>::size_type size_type;
  BlobPtr();
  BlobPtr(Blob<T>& a, size_type sz = 0) : wptr(a.data), curr(sz) {}
  // deference
  T& operator*() const;
  T& operator[](size_type);
  // increment/decrement
  BlobPtr& operator++();
  BlobPtr& operator--();
  BlobPtr& operator++(int);
  BlobPtr& operator--(int);
 private:
  std::shared_ptr<std::vector<T>> check(size_type, const std::string&) const;
  std::weak_ptr<std::vector<T>> wptr;
  size_type curr;
};
template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(
    size_type i, const std::string& msg) const {
  auto ret = wptr.lock();
  if (!ret) throw std::runtime_error("unbound BlobPtr");
  if (i >= ret->size()) throw std::out_of_range(msg);
  return ret;
}
// constructors
template <typename T>
BlobPtr<T>::BlobPtr() : curr(0) {}
// deference
template <typename T>
T& BlobPtr<T>::operator*() const {
  auto p = check(curr, "deference past end");
  return (*p)[curr];
}
// subscript
template <typename T>
T& BlobPtr<T>::operator[](size_type n) {
  auto p = check(curr + n, "subscript past end");
  return (*p)[curr + n];
}
// relational operator
template <typename T>
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
  return lhs.curr == rhs.curr;
}

// decrement and increment
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
  auto p = check(curr, "increment past end of BlobPtr");
  ++curr;
  return *this;
}
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
  --curr;
  auto p = check(curr, "decrement past begin of BlobPtr");
  return *this;
}
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int) {
  BlobPtr ret = *this;
  ++*this;
  return ret;
}
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int) {
  BlobPtr ret = *this;
  --*this;
  return ret;
}

#endif // BLOBPTR_H