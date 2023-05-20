/*
Задание 3
Измените программу из последнего подраздела «Вложенные циклы while»
так, чтобы она выводила следующее:
5 4 3 2 1
4 3 2 1
3 2 1
2 1
1
 */

#include <cstdint>
#include <iostream>


int main() {
  std::uint16_t outer = 5;
  while (outer >= 1) {
    std::uint16_t inner = outer;
    while (inner >= 1) {
      std::cout << inner-- << " ";
    }
    // Вставляем символ новой строки в конце каждого ряда
    std::cout << "\n";
    --outer;
  }
  return EXIT_SUCCESS;
}