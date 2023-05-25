#include <at_2_1/solution.hpp>


namespace at::at_2_1 {


answer solution(arg_t a, arg_t b, arg_t c) {
  if (a == b && a == c) {
    return answer::equilateral;
  }
  if (a == b || b == c || a == c) {
    return answer::isosceles;
  }
  return answer::scalene;
}


}// namespace at::at_2_1
