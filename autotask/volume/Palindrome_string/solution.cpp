/*
 * Напишите программу, которая принимает от пользователя строку и проверяет, является ли она палиндромом (читается одинаково слева направо и справа налево).
 * Программа должна игнорировать пробелы и знаки препинания при проверке.
 */

#include <Palindrome_string/solution.hpp>

#include <cctype>


namespace at::palindrome_string {


bool solution(std::string_view str) {

  const std::size_t size_of_string = str.size();
  std::size_t runner_1 = 0;
  std::size_t runner_2 = size_of_string - 1;

  if (size_of_string <= 0) {
    return true;
  }

  do {
    if (std::tolower(str[runner_1]) != std::tolower(str[runner_2])) {
      return false;
    }
    ++runner_1;
    --runner_2;
  } while (runner_1 <= (size_of_string / 2));

  return true;
}


}// namespace at::palindrome_string
