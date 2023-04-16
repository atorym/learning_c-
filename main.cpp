/*
Задание №2
Создайте структуру для хранения дробных чисел. Структура должна иметь 2 члена:
целочисленный числитель и целочисленный знаменатель. Объявите две дробные переменные
и получите их значения от пользователя. Напишите функцию multiply() (параметрами
которой будут эти две переменные), которая будет перемножать эти числа и выводить
результат в виде десятичного числа.
*/

#include <cstdint>
#include <iomanip>
#include <iostream>


// натуральная дробь
struct fraction {
  std::uint32_t numerator;
  std::uint32_t denominator;
};


//double multiply(fraction lhs, fraction rhs) {
//  return static_cast<double>(lhs.numerator * rhs.numerator) / (lhs.denominator * rhs.denominator);
//}


fraction multiply(fraction lhs, fraction rhs) {
  return {lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator};
}


int main() {
  std::cout << "Pls enter numerator, denominator of first fraction:\n";
  fraction lhs;
  std::cin >> lhs.numerator >> lhs.denominator;
  std::cout << "Pls enter numerator, denominator of second fraction:\n";
  fraction rhs;
  std::cin >> rhs.numerator >> rhs.denominator;

  auto result = multiply(lhs, rhs);
  std::cout << "Result of multiplying your fractions is: " << std::setprecision(3)
            << result.numerator / result.denominator << "\n";

  return EXIT_SUCCESS;
}
