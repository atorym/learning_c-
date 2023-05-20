/*
Задание №2
Напишите программу-игру типа Hi-Lo:

Во-первых, ваша программа должна выбрать случайное целое число в диапазоне от 1 до 100.
Пользователю дается 7 попыток, чтобы угадать это число.
Если пользователь не угадал число, то программа должна подсказывать, была ли его
догадка слишком большой или слишком маленькой. Если пользователь out of range, то количество попыток не уменьшается.
Если пользователь угадал число, то программа должна сообщить, что всё верно — вы выиграли.
Если же у пользователя кончились попытки, и он не угадал число, то программа должна сообщить
ему, что он проиграл и показать правильный результат.
В конце игры программа должна спросить у пользователя, не хочет ли он сыграть еще раз.
Если пользователь не введет ни y, ни n (а что-то другое), то программа должна спросить его еще раз.
 */

#include <cstdint>
#include <iostream>
#include <random>


using user_value_t = std::uint8_t;
enum class user_input_state:std::uint8_t;

user_value_t randomiser();
user_input_state comparison(user_value_t, user_value_t);
bool needed_more_request();
void game_session();


int main() {
  std::cout << "\tProgram Hi-Lo:\n";
  for (bool needed_more = true; needed_more; needed_more = needed_more_request()) {
    game_session();
  }
  return EXIT_SUCCESS;
}


user_value_t randomiser() {
  std::random_device rd;
  static std::mt19937 random_engine{rd()};
  return std::uniform_int_distribution<user_value_t>{0, 100}(random_engine);
}


enum class user_input_state:std::uint8_t {
  win,
  out_of_range,
  bigger,
  smaller
};


user_input_state comparison(user_value_t random_number, user_value_t user_number) {
  if (user_number == random_number) {
    return user_input_state::win;
  } else if (user_number < 1 || user_number > 100) {
    return user_input_state::out_of_range;
  } else if (user_number > random_number) {
    return user_input_state::bigger;
  } else /* if (user_number < random_number) */ {
    return user_input_state::smaller;
  }
}


bool needed_more_request() {
  std::cout << "Wanna fuck more?(y/n): ";
  std::string str;
  while (true) {
    std::cin >> str;
    if (str == "y") {
      return true;
    } else if (str == "n") {
      return false;
    }
    std::cout << "invalid input. Try again.(y/n): ";
  }
}


void game_session() {
  std::cout << "I'm create random int number in range of 0-100. You have 7 try's. Can you guess it?\n";
  user_value_t const random_number = randomiser();
  std::size_t i{};
  do {
    std::uint16_t user_number;
    std::cin >> user_number;
    switch (comparison(random_number, user_number)) {
      case user_input_state::win:
        std::cout << "Great, You won!\n";
        return;
      case user_input_state::out_of_range:
        std::cout << "Dear boy, You are balbes!\n";
        continue;
      case user_input_state::bigger:
        std::cout << "Your number is bigger then random\n";
        break;
      case user_input_state::smaller:
        std::cout << "Your number is smaller then random\n";
        break;
    }
    ++i;
  } while (i < 7);
}
