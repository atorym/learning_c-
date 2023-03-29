#include <iostream>

/*Задание
 Напишите программу, которая просит пользователя ввести число от 0 до 255.
 Выведите его как 8-битное двоичное число (в парах по 4 цифры). Не используйте побитовые операторы.
*/

int counter(std::uint16_t number, std::uint8_t bit) {
  //Принимает заданное число первым аргументом, вторым аргументом принимает бит, который необходимо узнать.
  if (number >= bit) {
    std::cout << "1";
    number -= bit;
  } else {
    std::cout << "0";
  }
  //Возвращает новое значение number в main, даже если оно не было изменено.
  return number;
}

int main() {
  std::cout << "Enter your number in range of 0 - 255:\n";
  std::uint16_t number{0};
  std::cin >> number;
  if ((number < 0) || (number > 255)) {
    std::cout << "Your number isn't correct.";
    return EXIT_SUCCESS;
  }

  std::cout << "Your number in binary system is: ";
  number = counter(number, 128);
  number = counter(number, 64);
  number = counter(number, 32);
  number = counter(number, 16);
  std::cout << " ";
  number = counter(number, 8);
  number = counter(number, 4);
  number = counter(number, 2);
  number = counter(number, 1);

  return EXIT_SUCCESS;
}