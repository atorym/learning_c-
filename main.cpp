/*
Задание №1
Напишите цикл for, который выводит каждое четное число в диапазоне от 0 до 20.
 */


#include <cstdint>
#include <iostream>

int main() {

  for (std::uint16_t number = 0; number <= 20; number += 2) {
    std::cout << number << " ";
  }

  return 0;
}
