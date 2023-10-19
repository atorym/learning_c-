#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <string_view>


std::int16_t ask_user();
int get_random_number(int min, int max);


int main() {
  //Настройка массива
  constexpr std::int16_t amount_of_name = 4;
  std::string_view name[amount_of_name] = {"Dima", "Akaky", "Anatoly", "Damokl"};
  std::string_view random_name = name[get_random_number(0, amount_of_name - 1)];

  std::string user_word_before;
  std::string user_word_after;
  //Основной loop программы
  while (1) {
    //Спрашиваем число
    std::int16_t user_number{0};
    user_number = ask_user();
    std::string current_word;

    switch (user_number) {
      case 1:
        std::cout << "What you want to enter?" << '\n';
        std::cin >> current_word;
        user_word_before += current_word;
        std::cout << user_word_before << ' ' << random_name << ' ' << user_word_after << '\n';
        break;

      case 2:
        std::cout << "What you want to enter?" << '\n';
        std::cin >> current_word;
        user_word_after += current_word;
        std::cout << user_word_before << ' ' << random_name << ' ' << user_word_after << '\n';
        break;

      case 3:
        return EXIT_SUCCESS;

      case 4:
        std::cout << "....Retrying...." << '\n'
                  << "................" << '\n';
        user_word_after = "";
        user_word_before = "";
        random_name = name[get_random_number(0, amount_of_name)];
        break;

      default: {
        std::cout << "Your number isn't correct. Repeat." << '\n';
        break;
      }
    }
    if (user_number == 3) {
      break;
    }
  }
  return EXIT_SUCCESS;
}

std::int16_t ask_user() {
  std::cout << "What you want to do?" << '\n'
            << "1)Enter a word before name" << '\n'
            << "2)Enter word after name" << '\n'
            << "3)Exit" << '\n'
            << "4)Retry" << '\n';
  std::int16_t user_numer = 0;
  std::cin >> user_numer;
  return user_numer;
}

//Получаем рандомное число из заданного диапазона. Доделать!
int get_random_number(int min, int max) {
  //Настройка генератора случайных чисел Вихря Мерсенна.
  std::random_device rd;
  std::mt19937 mersenne(rd());
  //Генерация случайного числа в заданном диапазоне
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(mersenne);
}