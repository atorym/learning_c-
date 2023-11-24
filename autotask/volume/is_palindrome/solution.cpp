#include <algorithm>
#include <is_palindrome/solution.hpp>
#include <string>
#include <vector>


namespace at::is_palindrome {


bool is_palindrome_func(std::string_view in) {


  //обработка исключений
  if (in.size() == 1 || in.size() == 0) {
    return true;
  }

  std::string inverted_array_copy;
  std::copy(in.crbegin(), in.crend(), std::back_inserter(inverted_array_copy));

  for (std::size_t i = 0; i <= in.size(); ++i) {
    if (in[i] != inverted_array_copy[i]) {
      return false;
    }
  }
  return true;
}


}// namespace at::is_palindrome
