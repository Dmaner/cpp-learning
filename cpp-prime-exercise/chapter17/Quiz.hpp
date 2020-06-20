#ifndef QUIZ_H
#define QUIZ_H

#include <bitset>
#include <iostream>

template <unsigned M>
class Quiz {
  template <unsigned N>
  friend int result(const Quiz<N>&, const Quiz<N>&);
  template <unsigned N>
  friend std::ostream& operator<<(std::ostream&, const Quiz<N>&);

 public:
  Quiz();
  Quiz(const std::string& s) : answers(s){};
  void set(size_t, bool);

 private:
  std::bitset<M> answers;
};

template <unsigned M>
std::ostream& operator<<(std::ostream& os, const Quiz<M>& quiz) {
  return os << quiz.answers;
}

template <unsigned M>
void Quiz<M>::set(size_t pos, bool ans) {
  answers[pos] = ans;
}

template <unsigned M>
int result(const Quiz<M>& stu, const Quiz<M>& ans) {
  std::bitset<M> res = stu.answers ^ ans.answers;
  res.flip();
  return res.count();
}

#endif