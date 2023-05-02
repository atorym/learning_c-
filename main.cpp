/*
Задание №2
Напишите функцию sumTo(), которая принимает целочисленный параметр с именем value и возвращает сумму всех чисел от 1 до значения value.
Например, если значением value является 5, то sumTo(5) должен возвратить 15, исходя из 1 + 2 + 3 + 4 + 5.
 */


#include <cstdint>
#include <iostream>

std::uint32_t sumTo(std::uint16_t);

int main() {
  std::cout << "Pls enter your int positive value: ";
  std::uint16_t value;
  std::cin >> value;
  std::cout << "Sum of numbers from 1 to " << value << " is: " << sumTo(value);

  return 0;
}

std::uint32_t sumTo(std::uint16_t value) {
  std::uint32_t sum = 0;
  for (std::uint16_t counter = 0; counter <= value; ++counter)
    sum = sum + counter;
  return sum;
}
