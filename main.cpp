/*
Задание 1
Почему в программе, приведенной выше, переменная inner объявлена внутри блока while,
а не сразу после объявления переменной outer (вне блока while)?
Чтобы счет при переходе на новую строку начинался каждый раз по новой (каждый раз при выполнении внешнего цикла)
и в строке происходил счет 1,2 и т.д.
Задание 2
Напишите программу, которая выводит буквы английского алфавита от a до z вместе с кодами из ASCII-таблицы.
 */

#include <cstdint>
#include <iostream>


int main() {
  std::uint8_t counter = 'a';
  while (counter <= 'z') {
    std::cout << static_cast<char>(counter) << " has " << static_cast<std::int32_t>(counter) << " dex number in ASCII table.\n";
    ++counter;
  }
  return EXIT_SUCCESS;
}
