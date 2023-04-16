/*
Задание №1
У вас есть веб-сайт и вы хотите отслеживать, сколько денег вы зарабатываете в день
от размещенной на нем рекламы. Объявите структуру Advertising, которая будет отслеживать:
*сколько объявлений вы показали посетителям (1);
*сколько процентов посетителей нажали на объявления (2);
*сколько вы заработали в среднем за каждое нажатие на объявления (3).
Значения этих трех полей должен вводить пользователь. Передайте структуру Advertising в функцию,
которая выведет каждое из этих значений, а затем подсчитает, сколько всего денег вы заработали
за день (перемножьте все 3 поля).
*/

#include <cstdint>
#include <iostream>


struct Advertising {
  std::uint32_t quantity;
  double percent;
  double money;


  friend std::ostream& operator<<(std::ostream& os, const Advertising& advertising) {
    os << "Here is user statistic:\n"
       << "Quantity of announcement: " << advertising.quantity << "\n"
       << "Percent of user's activity: " << advertising.percent << "\n"
       << "Average earnings from 1 user: " << advertising.money << "\n"
       << "Amount of money for 1 day: " << advertising.quantity * advertising.percent * advertising.money << "\n";
    return os;
  }


  friend std::istream& operator<<(std::istream& os, Advertising& advertising) {
    os >> advertising.quantity >> advertising.percent >> advertising.money;
    return os;
  }
};


int main() {
  std::cout << "Enter first user quantity of announcement, percent of user's clicks, average earnings from 1 user:\n";
  Advertising user1;
  std::cin >> user1;

  std::cout << user1 << '\n';

  return EXIT_SUCCESS;
}
