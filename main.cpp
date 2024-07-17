/*
Задание №2

Реализуйте класс Pair, который позволяет пользователю использовать разные типы данных в передаваемых парах.

Следующий код:

   int main()
{
 Pair<int, double> p1(6, 7.8);
 std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

 const Pair<double, int> p2(3.4, 5);
 std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

 return 0;
}

Должен выдавать следующий результат:
   Pair: 6 7.8
   Pair: 3.4 5

   */

#include <iostream>


   template<class T, class Y>
   class Pair {
private:
 T value1_;
 Y value2_;

public:
 Pair(T &value1, Y &value2)
     : value1_{value1}
     , value2_{value2} {}

 friend std::ostream& operator<<(std::ostream& out, const Pair& pair1) {
   out << pair1.value1_ << ' ' << pair1.value2_;
   return out;
 }

 T first() const {
   return value1_;
 }

 Y second() const {
   return value2_;
 }
};


int main() {

 Pair<int, double> p1(6, 7.8);
 std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

 const Pair<double, int> p2(3.4, 5);
 std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

 return EXIT_SUCCESS;
};