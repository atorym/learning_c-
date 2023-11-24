#include <is_palindrome/solution.hpp>

#include <algorithm>
#include <string>
#include <vector>


namespace at::is_palindrome {


bool is_palindrome_func(std::string_view in) {
  for(auto it = in.cbegin(); it != in.cend(); ++it) {
    auto const it_b = in.crbegin() + (it - in.cbegin());
    if(*it != *it_b) {
      return false;
    }
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
