/*
Задание №2
Напишите программу-игру типа Hi-Lo:

Во-первых, ваша программа должна выбрать случайное целое число в диапазоне от 1 до 100.
Пользователю дается 7 попыток, чтобы угадать это число.
Если пользователь не угадал число, то программа должна подсказывать, была ли его
догадка слишком большой или слишком маленькой.
Если пользователь угадал число, то программа должна сообщить, что всё верно — вы выиграли.
Если же у пользователя кончились попытки, и он не угадал число, то программа должна сообщить
ему, что он проиграл и показать правильный результат.
В конце игры программа должна спросить у пользователя, не хочет ли он сыграть еще раз.
Если пользователь не введет ни y, ни n (а что-то другое), то программа должна спросить его еще раз.
 */

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>


std::int16_t randomizer();
bool comparison(std::int16_t, std::int16_t);
std::uint8_t check_input();


int main() {
  srand(static_cast<std::uint16_t>(std::time(0)));
  std::cout << "Program Hi-Lo:\n";
start_again:
  std::cout << "I'm create random int number in range of 0-100. You have 7 try's. Can you guess it?\n";
  std::int16_t random_number = randomizer();
  std::int8_t counter{0};
  while (counter < 7) {
    std::int16_t user_number;
    std::cin >> user_number;
    if (comparison(random_number, user_number)) {
      std::cout << "You win!\n";
      break;
    }
    ++counter;
  }
repeat:
  std::uint8_t decision = check_input();
  if (decision == 'y') {
    goto start_again;
  } else if (decision == 'n') {
    return EXIT_SUCCESS;
  } else {
    goto repeat;
  }
}


std::int16_t randomizer() {
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (100 - 0 + 1) + 0);
}


bool comparison(std::int16_t random_number, std::int16_t user_number) {
  bool status;
  if (user_number < 0 || user_number > 100) {
    std::cout << "Your number is out of range!\n";
    status = false;
  } else if (user_number > random_number) {
    std::cout << "Your number is bigger then random.\n";
    status = false;
  } else if (user_number < random_number) {
    std::cout << "Your number is smaller then random.\n";
    status = false;
  } else {
    std::cout << "Great! You got it!\n";
    status = true;
  }
  return status;
}


std::uint8_t check_input() {
  std::cout << "Would you like to try again?(y/n)\n";
  std::uint8_t decision;
  std::cin >> decision;
  if (decision == 'y' || decision == 'n')
    return decision;
  else
    std::cout << "Input is invalid, pls try again!\n";
}