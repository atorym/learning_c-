#include <cstdint>
#include <iostream>
#include <string>


std::string empty_space(std::uint16_t number) {
  switch (number) {
    case 1:
      return "        ";
    case 2:
      return "      ";
    case 3:
      return "    ";
    case 4:
      return "  ";
    default:
      return "";
  }
}


int main() {
  std::uint16_t outer = 1;
  while (outer <= 5) {
    std::cout << empty_space(outer);
    std::uint16_t inner = outer;
    while (inner >= 1) {
      std::cout << inner-- << " ";
    }
    // Вставляем символ новой строки в конце каждого ряда
    std::cout << "\n";
    ++outer;
  }
  return EXIT_SUCCESS;
}
