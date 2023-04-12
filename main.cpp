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
#include <iostream>
#include <stdint.h>


struct Advertising {
  std::uint32_t quantity{0};
  double percent{0};
  double money{0};
};

void counter(Advertising advertising) {
  using namespace std;
  cout << "Here is user statistic:\n";
  cout << "Quantity of announcement: " << advertising.quantity << "\n";
  cout << "Percent of user's activity: " << advertising.percent << "\n";
  cout << "Average earnings from 1 user: " << advertising.money << "\n";
  cout << "Amount of money for 1 day: " << advertising.quantity * advertising.percent * advertising.money << "\n";
}

int main() {
  std::cout << "Enter first user quantity of announcement, percent of user's clicks, average earnings from 1 user:\n";
  Advertising user1{};
  std::cin >> user1.quantity >> user1.percent >> user1.money;
  counter(user1);
  return EXIT_SUCCESS;
}
