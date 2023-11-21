#include <is_palindrome/solution.hpp>


namespace at::is_palindrome {


bool is_palindrome_func(std::string_view in) {
  std::size_t count_of_polindrome = true;
  for (std::size_t i = 0, j = in.size(); i != in.size() / 2; ++i, --j) {
    if (in[i] != in[j]) {
      count_of_polindrome = false;
      break;
    }
  }
  return count_of_polindrome;
}


}// namespace at::is_palindrome
