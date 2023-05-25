#include <at_2_4/solution.hpp>

#include <sstream>
#include <string>


namespace at::at_2_4 {
namespace {
namespace _ {


// https://stackoverflow.com/a/22999488
answer_value addToAverage(answer_value average, std::size_t size, answer_value value) {
  return (size * average + value) / (size + 1);
}


}// namespace _
}// namespace


answer solution(std::istringstream&& iss) {
  answer answer{};
  answer_value read;
  std::size_t counter{};
  while (true) {
    iss >> read;
    if (read < 0) {
      break;
    }
    answer.sum += read;
    answer.max = std::max(answer.max, read);
    answer.average = _::addToAverage(answer.average, counter, read);
    ++counter;
  }
  return answer;
}


}// namespace at::at_2_4
