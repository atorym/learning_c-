/*
Задание №2
Добавьте перегрузку операторов << и < в класс Car, представленный выше, чтобы следующий фрагмент кода:
(код указан в main)
Выдавал следующий результат:
(Ford, Mustang)
(Ford, Ranger)
(Renault, Duster)
(Renault, Logan)
*/


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


class Car {
private:
 std::string m_company;
 std::string m_model;

public:
 Car(std::string company, std::string model)
     : m_company(company)
     , m_model(model) {}

 friend bool operator==(const Car& c1, const Car& c2);
 friend bool operator!=(const Car& c1, const Car& c2);
 friend bool operator>(const Car& c1, const Car& c2);
 friend bool operator<(const Car& c1, const Car& c2);

 friend std::ostream& operator<<(std::ostream& out, const Car& c1);
};


bool operator==(const Car& c1, const Car& c2) {
 return (c1.m_company == c2.m_company || c1.m_model == c2.m_model);
}

bool operator!=(const Car& c1, const Car& c2) {
 return !(c1 == c2);
}

bool operator>(const Car& c1, const Car& c2) {
 if (c1.m_company >= c2.m_company) {
   return (c1.m_model > c2.m_model);
 } else {
   return false;
 }
}

bool operator<(const Car& c1, const Car& c2) {
 if (c1.m_company < c2.m_company) {
   return (c1.m_company < c2.m_company);
 } else {
   return false;
 }
}

std::ostream& operator<<(std::ostream& out, const Car& c1) {
 out << c1.m_company << ' ' << c1.m_model << '\n';
 return out;
}

int main() {
 std::vector<Car> v;
 v.push_back(Car("Ford", "Mustang"));
 v.push_back(Car("Renault", "Logan"));
 v.push_back(Car("Ford", "Ranger"));
 v.push_back(Car("Renault", "Duster"));

 std::sort(v.begin(), v.end());
 // требуется перегрузка оператора < для класса Car
 for (auto& car : v)
   std::cout << car << '\n';
 // требуется перегрузка оператора << для класса Car

 return EXIT_SUCCESS;
}