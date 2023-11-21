#include <is_palindrome/solution.hpp>


namespace at::is_palindrome {


std::size_t is_palindrome(std::string_view in) {
  std::size_t count_of_polindrome;
  for (std::size_t i = 0, j = in.size(); i != in.size()/2; ++i, --j) {
    if(in[i] != in[j]){

    }
  }

  return count_of_polindrome;
}


} // namespace at::is_palindrome
