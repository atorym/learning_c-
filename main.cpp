/*
Задание №3

Напишите шаблон класса StringValuePair, в котором первое значение всегда является типа string_, а второе может
быть любого типа. Этот шаблон класса должен наследовать частично специализированный класс Pair (в котором
первый параметр типа std::string_, а второй — «любой тип данных»).

  Следующий код:

   int main()
{
 StringValuePair<int> svp("Amazing", 7);
 std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

 return 0;
}

Должен выдавать следующий результат:

   Pair: Amazing 7

          */

#include <iostream>
#include <string>


          template<class S, class T>
          class Pair {
protected:
 S string_;
 T value2_;

public:
 Pair(const S& letter, const T& value2)
     : string_{letter}
     , value2_{value2} {}

 S& first() {
   return string_;
 }

 const S& first() const {
   return string_;
 }

 T& second() {
   return value2_;
 }

 const T& second() const {
   return value2_;
 }
};


template<class T>
class StringValuePair : public Pair<std::string, T> {
private:
public:
 StringValuePair(const std::string& letter, const T& value2)
     : Pair<std::string, T>(letter, value2) {}
};


int main() {
 StringValuePair<int> svp("Amazing", 7);
 std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

 return 0;

 return EXIT_SUCCESS;
};