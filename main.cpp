/*
Задание №2
Создайте структуру для хранения дробных чисел. Структура должна иметь 2 члена:
целочисленный числитель и целочисленный знаменатель. Объявите две дробные переменные
и получите их значения от пользователя. Напишите функцию multiply() (параметрами
которой будут эти две переменные), которая будет перемножать эти числа и выводить
результат в виде десятичного числа.
*/

#include <iostream>
#include <stdint.h>
#include <iomanip>

struct fraction {
  std::uint32_t numerator{};
  std::uint32_t denominator{};
};

void multiply(fraction lhs, fraction rhs) {
  double result{static_cast<double >(lhs.numerator*rhs.numerator)/(lhs.denominator*rhs.denominator)};
  std::cout << "Result of multiplying your fractions is: " << std::setprecision(3) << result << "\n";
}

int main() {

  using std::cin;
  using std::cout;
  cout << "Pls enter numerator, denominator of first fraction:\n";
  fraction lhs{};
  cin >> lhs.numerator >> lhs.denominator;
  cout << "Pls enter numerator, denominator of second fraction:\n";
  fraction rhs{};
  cin >> rhs.numerator >> rhs.denominator;
  multiply(lhs, rhs);

  return EXIT_SUCCESS;
}
