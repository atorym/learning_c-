/*
Задание №1

Предположим, что нам нужно передавать данные парами. Реализуйте шаблон класса Pair1, который позволяет пользователю
                                                                                     передавать данные одного типа парами.

                                                                                   Следующий код:

   int main()
{
 Pair1<int> p1(6, 9);
 std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

 const Pair1<double> p2(3.4, 7.8);
 std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

 return 0;
}

Должен выдавать следующий результат:

   Pair: 6 9
   Pair: 3.4 7.8

   */

#include <iostream>


   template<class T>
   class Pair1 {
private:
 T value1_;
 T value2_;

public:
 Pair1(T &value1, T &value2)
     : value1_{value1}
     , value2_{value2} {}

 friend std::ostream& operator<<(std::ostream& out, const Pair1& pair1) {
   out << pair1.value1_ << ' ' << pair1.value2_;
   return out;
 }

 T first() const {
   return value1_;
 }

 T second() const {
   return value2_;
 }
};


int main() {
 Pair1<int> p1(6, 9);
 std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

 const Pair1<double> p2(3.4, 7.8);
 std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

 return EXIT_SUCCESS;
};