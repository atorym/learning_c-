/*
Тест
a) Напишите класс Fraction, который имеет два целочисленных члена: числитель и знаменатель.
Реализуйте функцию print(), которая будет выводить дробь.

Следующий фрагмент кода:
int main()
{
Fraction f1(1, 4);
f1.print();

Fraction f2(1, 2);
f2.print();
}

Должен выдавать следующий результат:
1/4
1/2

b) Добавьте перегрузку оператора умножения (*) для выполнения операции умножения объекта класса
Fraction на целочисленное значение и для перемножения двух объектов класса Fraction. Используйте
способ перегрузки оператора через дружественную функцию. Подсказка: Умножение двух дробей
осуществляется умножением двух числителей, а затем отдельно двух знаменателей. Для выполнения
операции умножения объекта на целочисленное значение, умножьте только числитель на целочисленное
значение (знаменатель не трогайте).

Следующий фрагмент кода:
#include <iostream>

int main()
{
Fraction f1(3, 4);
f1.print();

Fraction f2(2, 7);
f2.print();

Fraction f3 = f1 * f2;
f3.print();

Fraction f4 = f1 * 3;
f4.print();

Fraction f5 = 3 * f2;
f5.print();

Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
f6.print();
}

Должен выдавать следующий результат:
3/4
2/7
6/28
9/4
6/7
6/24

Дополнительное задание
c) Дробь 2/4 — это та же дробь, что и 1/2, только 1/2 не делится до минимальных неделимых значений. Мы можем уменьшить любую заданную дробь до наименьших значений, найдя наибольший общий делитель (НОД) для числителя и знаменателя, а затем выполнить деление как числителя, так и знаменателя на НОД.
Ниже приведена функция поиска НОД: 1. int nod(int a, int b) { 2. return (b == 0) ? (a > 0 ? a : -a) : nod(b, a % b); 3. }
Добавьте эту функцию в ваш класс и реализуйте метод reduce(), который будет уменьшать дробь. Убедитесь, что дробь будет максимально и корректно уменьшена.

Следующий фрагмент кода:
#include <iostream>

   int main()
{
 Fraction f1(3, 4);
 f1.print();

 Fraction f2(2, 7);
 f2.print();

 Fraction f3 = f1 * f2;
 f3.print();

 Fraction f4 = f1 * 3;
 f4.print();

 Fraction f5 = 3 * f2;
 f5.print();

 Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
 f6.print();

 return 0;
}

Должен выдавать следующий результат:
 3/4
 2/7
 3/14
 9/4
 6/7
 1/4
 */

#include <cstdint>
#include <iostream>


 class Fraction {
private:
 std::size_t nominator_;
 std::size_t denominator_;

public:
 Fraction(std::size_t chislitel, std::size_t snamenatel)
     : nominator_{chislitel}
     , denominator_{snamenatel} {}

 void print() {
   std::cout << nominator_ << '/' << denominator_ << '\n';
 }


 static int nod(int a, int b) {
   return (b == 0) ? (a > 0 ? a : -a) : nod(b, a % b);
 }

 static Fraction reduce(Fraction f) {
   return Fraction(f.nominator_ / nod(f.denominator_, f.nominator_),
     f.denominator_ / nod(f.denominator_, f.nominator_));
 }

 friend Fraction operator*(const Fraction& f1, const Fraction& f2);
 friend Fraction operator*(const Fraction& f1, const int& number);
 friend Fraction operator*(const int& number, const Fraction& f1);

};


Fraction operator*(const Fraction& f1, const Fraction& f2) {

 int nominator = f1.nominator_ * f2.nominator_;
 int denominator = f1.denominator_ * f2.denominator_;

 return Fraction::reduce(Fraction(nominator, denominator));
}

Fraction operator*(const Fraction& f1, const int& number) {
 int nominator = f1.nominator_ * number;
 return Fraction::reduce(Fraction(nominator, f1.denominator_));
}

Fraction operator*(const int& number, const Fraction& f1) {
 return f1 * number;
}


int main() {
 Fraction f1(3, 4);
 f1.print();

 Fraction f2(2, 7);
 f2.print();

 Fraction f3 = f1 * f2;
 f3.print();

 Fraction f4 = f1 * 3;
 f4.print();

 Fraction f5 = 3 * f2;
 f5.print();

 Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
 f6.print();

 return EXIT_SUCCESS;
}