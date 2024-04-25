/*
Задание №4
Значение типа с плавающей точкой — это число с десятичной дробью, где количество цифр после точки (дробная часть)
может меняться. Значение типа с фиксированной точкой — это число с дробью, где дробь (после точки) фиксированная.

Вам нужно написать класс для реализации значений типа с фиксированной точкой с двумя цифрами после точки
(например, 11.47, 5.00 или 1465.78). Диапазон класса должен быть от -32768.99 до 32767.99, в дробной части могут
быть любые две цифры, не допускайте проблем с точностью.

a) Какого типа данных переменную-член следует использовать для реализации значений типа с фиксированной точкой с
2-мя цифрами после точки? (Обязательно прочитайте ответ, прежде чем приступать к выполнению следующего задания)

b) Напишите класс FixedPoint, который реализует рекомендуемое решение из предыдущего задания. Если дробная или
целая части значения являются отрицательными, то число должно рассматриваться, как отрицательное. Реализуйте
перегрузку необходимых операторов и напишите необходимые конструкторы, чтобы следующий код функции main():

*Приведен в функции main();

Выдавал следующий результат:

37.58
-3.09
-4.07
-5.07
-0.03
-0.03

c) Теперь добавьте конструктор, который будет принимать значение типа double. Вы можете округлить целую часть
(слева от точки) с помощью функции round() (которая находится в заголовочном файле cmath).

Следующий код функции main():

*Приведен в функции main();

Должен выдавать следующий результат:

0.03
-0.03
4.01
-4.01

d) Выполните перегрузку следующих операторов: ==, >>, − (унарный) и + (бинарный).
Следующая программа:

*Код приведен в функциях main() и SomeTest();

Должна выдавать следующий результат:
    true
    true
    true
    true
    true
    true
    true
    true
    -0.48
        0.48
        Enter a number: 5.678
        You entered: 5.68
        */

#include <cmath>
#include <cstdint>
#include <iostream>


        class FixedPoint {
private:
  std::int16_t base_;
  std::int8_t suppliment_;

public:
  FixedPoint(std::int16_t base, std::int8_t suppliment)
      : base_(base)
      , suppliment_(suppliment) {
  }
  FixedPoint(double drob) {
    base_ = std::round(drob);
    suppliment_ = static_cast<std::int8_t>(round(drob * 100)) - (base_ * 100);
  }

  operator double() const {

    return base_ + static_cast<double>(suppliment_) / 100;
  }

  FixedPoint operator+(const FixedPoint& rhs) {
    this->base_ += rhs.base_;
    this->suppliment_ += rhs.suppliment_;
    if (this->suppliment_ > 100) {
      this->base_ += 1;
      this->suppliment_ -= 100;
    }

    return *this;
  }

  FixedPoint operator-(const FixedPoint& rhs) {
    this->base_ -= rhs.base_;
    this->suppliment_ -= rhs.suppliment_;

    return *this;
  }

  bool operator==(const FixedPoint& rhs) {
    if (static_cast<double>(*this) == static_cast<double>(rhs)) {

      return true;
    }

    return false;
  }

  FixedPoint operator-() const {

    return FixedPoint(-base_, -suppliment_);
  }

  friend std::ostream& operator<<(std::ostream& out, const FixedPoint& value);
  friend std::istream& operator>>(std::istream& in, FixedPoint& value);
};


std::ostream& operator<<(std::ostream& out, const FixedPoint& value) {
  out << static_cast<double>(value);

  return out;
}


std::istream& operator>>(std::istream& in, FixedPoint& value) {
  double temp;
  in >> temp;
  //если идет ввод 2-х значений типа int
  if (round(temp) == temp) {
    value.base_ = static_cast<std::int16_t>(round(temp));
    in >> temp;
    value.suppliment_ = static_cast<std::int8_t>(temp);
  } else {
    //если идет ввод значения типа double
    value.base_ = round(temp);
    value.suppliment_ = static_cast<std::int8_t>(round(temp * 100)) - (value.base_ * 100);
  }

  return in;
}

// Задание D
void SomeTest() {
  std::cout << std::boolalpha;
  std::cout << (FixedPoint(0.75) + FixedPoint(1.23) == FixedPoint(1.98)) << '\n';   // оба значения положительные, никакого переполнения
  std::cout << (FixedPoint(0.75) + FixedPoint(1.50) == FixedPoint(2.25)) << '\n';   // оба значения положительные, переполнение
  std::cout << (FixedPoint(-0.75) + FixedPoint(-1.23) == FixedPoint(-1.98)) << '\n';// оба значения отрицательные, никакого переполнения
  std::cout << (FixedPoint(-0.75) + FixedPoint(-1.50) == FixedPoint(-2.25)) << '\n';// оба значения отрицательные, переполнение
  std::cout << (FixedPoint(0.75) + FixedPoint(-1.23) == FixedPoint(-0.48)) << '\n'; // второе значение отрицательное, никакого переполнения
  std::cout << (FixedPoint(0.75) + FixedPoint(-1.50) == FixedPoint(-0.75)) << '\n'; // второе значение отрицательное, возможно переполнение
  std::cout << (FixedPoint(-0.75) + FixedPoint(1.23) == FixedPoint(0.48)) << '\n';  // первое значение отрицательное, никакого переполнения
  std::cout << (FixedPoint(-0.75) + FixedPoint(1.50) == FixedPoint(0.75)) << '\n';  // первое значение отрицательное, возможно переполнение
}


int main() {

  //  //задание B
  //  FixedPoint a(37, 58);
  //  std::cout << a << '\n';
  //
  //  FixedPoint b(-3, 9);
  //  std::cout << b << '\n';
  //
  //  FixedPoint c(4, -7);
  //  std::cout << c << '\n';
  //
  //  FixedPoint d(-5, -7);
  //  std::cout << d << '\n';
  //
  //  FixedPoint e(0, -3);
  //  std::cout << e << '\n';
  //
  //  std::cout << static_cast<double>(e) << '\n';

  //    // Задание C
  //    FixedPoint a(0.03);
  //    std::cout << a << '\n';
  //
  //    FixedPoint b(-0.03);
  //    std::cout << b << '\n';
  //
  //    FixedPoint c(4.01);// сохранится, как 4.0099999..., поэтому нам нужно это всё округлить
  //    std::cout << c << '\n';
  //
  //    FixedPoint d(-4.01);// сохранится, как -4.0099999…, поэтому нам нужно это всё округлить
  //    std::cout << d << '\n';

  // Задание D
  SomeTest();

  FixedPoint a(-0.48);
  std::cout << a << '\n';

  std::cout << -a << '\n';

  std::cout << "Enter a number: ";// введите 5.678
  std::cin >> a;

  std::cout << "You entered: " << a << '\n';

  return EXIT_SUCCESS;
}