#include <is_palindrome/solution.hpp>

#include <algorithm>
#include <string>
#include <vector>


namespace at::is_palindrome {


bool is_palindrome_func(std::string_view in) {
  auto it_forward = in.cbegin();
  auto it_backward = in.crbegin();
  while (it_forward != in.cend()) {
    if (*it_forward != *it_backward) {
      return false;
    }
    ++it_forward;
    ++it_backward;
  }
  return true;

  //  if (in.empty()) {
  //    return true;
  //  }
  //
  //  for (std::size_t i_f = 0; i_f < in.size() / 2; ++i_f) {
  //    if (in[i_f] != in[in.size() - 1 - i_f]) {
  //      return false;
  //    }
  //  }
  //  return true;
}


}// namespace at::is_palindrome
