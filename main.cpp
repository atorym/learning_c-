/*
Задание №1
Напишите функцию calculate(), которая принимает две переменные типа int и одну переменную типа char,
которая, в свою очередь, представляет одну из следующих математических операций: +, -, *, / или %
(остаток от числа). Используйте switch для выполнения соответствующей математической операции над целыми числами,
а результат возвращайте обратно в main(). Если в функцию передается недействительный математический оператор,
то функция должна выводить ошибку. С оператором деления выполняйте целочисленное деление.
*/

#include <cstdint>
#include <iostream>
#include <stdexcept>


std::int16_t calculate(std::int16_t lhs, std::int16_t rhs, char operation) {
  switch (operation) {
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    default:
      throw std::runtime_error{"ERROR"};
  }
}


int main() {
  std::cout << calculate(32, 16, '/');
  return EXIT_SUCCESS;
}
