#include <cmath>
#include <iostream>
#include <regex>
#include <tuple>

#include "Quiz.hpp"

void exc_17_1() {
  std::cout << "EXercise 17.1\n";
  std::tuple<int, int, int> tuple{10, 20, 30};
  std::cout << std::get<0>(tuple) << std::endl;
  std::cout << std::get<1>(tuple) << std::endl;
  std::cout << std::get<2>(tuple) << std::endl;
}

void exc_17_11() {
  std::cout << "EXercise 17.11 17.12 17.13\n";
  // Ex17_11
  std::string s = "1010101";
  Quiz<10> quiz(s);
  std::cout << quiz << std::endl;

  // EX17_12
  quiz.set(1, true);
  std::cout << quiz << std::endl;

  // Ex17_13
  std::string answer = "10011";
  std::string stu_answer = "11001";
  Quiz<5> ans(answer), stu_ans(stu_answer);
  std::cout << result(ans, stu_ans) << std::endl;
}

void exc_17_15() {
  std::cout << "Exercise 17.15\n";
  std::regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*", std::regex::icase);
  std::string result;
  std::string test = "String Test: cei, fei, ei";
  if (std::regex_match(test, r)) {
    std::cout << "Match!" << std::endl;
  } else {
    std::cout << "No Match!" << std::endl;
  }
}

void exc_17_17() {
  std::cout << "Exercise 17.17\n";
  std::regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*", std::regex::icase);
  std::string test = "String Test: cei, fei, fsei";
  for (std::sregex_iterator it(test.begin(), test.end(), r), end_it;
       it != end_it; ++it) {
    std::cout << "Match Word: " << it->str() << std::endl;
  }
}

void exc_17_19() {
  std::cout << "Exercise 17.19\n";
  std::string phone_regex =
      "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
  std::regex r(phone_regex);
  std::string test = "555-678-7412";
  if (std::regex_match(test, r)) {
    std::cout << "Standard phone number\n";
  } else {
    std::cout << "No phone number\n";
  }
}

void exc_17_35() {
  std::cout << "Exercise 17.35\n"
            << "default format: " << 100 * std::sqrt(2.0) << '\n'
            << "scientific: " << std::scientific << 100 * sqrt(2.0) << '\n'
            << "fixed decimal: " << std::fixed << 100 * sqrt(2.0) << '\n'
            << "hexidecimal: " << std::uppercase << std::hexfloat
            << 100 * sqrt(2.0) << '\n'
            << "use defaults: " << std::defaultfloat << 100 * sqrt(2.0)
            << "\n";
}

int main(int argc, char const *argv[]) {
  exc_17_1();
  exc_17_11();
  exc_17_15();
  exc_17_17();
  exc_17_19();
  exc_17_35();
  return 0;
}
