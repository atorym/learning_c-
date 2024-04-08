/*
Тест
Задание №1 Используя класс Dollars, приведенный выше, перепишите операторы < и <=, используя их
логические противоположности.
*/


#include <iostream>


class Dollars {
private:
  int dollars_;

public:
  Dollars(int dollars) { dollars_ = dollars; }

  friend bool operator>(const Dollars& d1, const Dollars& d2);
  friend bool operator<=(const Dollars& d1, const Dollars& d2);

  friend bool operator<(const Dollars& d1, const Dollars& d2);
  friend bool operator>=(const Dollars& d1, const Dollars& d2);
};

bool operator>(const Dollars& d1, const Dollars& d2) {
  return d1.dollars_ > d2.dollars_;
}

bool operator>=(const Dollars& d1, const Dollars& d2) {
  return d1.dollars_ >= d2.dollars_;
}

bool operator<(const Dollars& d1, const Dollars& d2) {
  return !(operator>=(d1,d2));
}

bool operator<=(const Dollars& d1, const Dollars& d2) {
  return !(operator>(d1,d2));
}


int main() {
  Dollars ten(10);
  Dollars seven(7);

  if (ten > seven)
    std::cout << "Ten dollars are greater than seven dollars.\n";
  if (ten >= seven)
    std::cout << "Ten dollars are greater than or equal to seven dollars. \n";
  if (ten < seven)
    std::cout << "Seven dollars are greater than ten dollars.\n";
  if (ten <= seven)
    std::cout << "Seven dollars are greater than or equal to ten dollars. \n";

  return EXIT_SUCCESS;
}