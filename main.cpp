/*
Тест
Напишите класс Fraction, конструктор которого принимает числитель и знаменатель. Если пользователь передал в качестве
знаменателя 0, то выбрасывайте исключение типа std::runtime_error (которое находится в заголовочном файле stdexcept).
В функции main() попросите пользователя ввести два целых числа. Если числа, которые ввел пользователь, корректные,
то выводите создаваемый объект класса Fraction. Если же числа недопустимые, то вы должны обрабатывать исключение типа
std::exception и сообщить пользователю, что он ввел некорректные данные.

Подсказка:
    std::runtime_error является дочерним классу-исключению std::exception, поэтому у вас должен быть только один блок catch.

        Пример выполнения программы:

    Enter the numerator: 7
    Enter the denominator: 0
    Your fraction has an invalid denominator.
      */

#include <iostream>
#include <stdexcept>
#include <string>


        class Fraction {
private:
  int numerator_;
  int denominator_;

public:
  Fraction(int numerator, int denominator)
      : numerator_{numerator}
      , denominator_{denominator} {

    if (denominator_ == 0) {
      denominator_ = 1;
      throw std::runtime_error("Zero denominator is an exception!");
    }
  }

  int& get_nominator() {
    return numerator_;
  }
  int& get_denominator() {
    return denominator_;
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
    out << fraction.numerator_ << "/" << fraction.denominator_;
    return out;
  }
};


int main() {

  std::cout << "Enter the numerator: ";
  int numerator;
  std::cin >> numerator;
  std::cout << "Enter the denominator: ";
  int denominator;
  std::cin >> denominator;

  try {
    Fraction fraction{numerator, denominator};
    std::cout << "Your fraction is " << fraction << " .";
  }
  
  catch (std::runtime_error) {
    std::cerr << "Your fraction has invalid denominator\n";
  }


  return EXIT_SUCCESS;
}