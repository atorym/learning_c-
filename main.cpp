#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>


int main() {

  std::cout << "How many names would you like to enter?" << '\n';
  std::int16_t user_count;
  while (true) {
    std::cin >> user_count;
    if (user_count <= 0) {
      std::cout << "Pls repeat." << '\n';
    } else {
      break;
    }
  }
  //инициализация массива имен
  auto* name_array = new std::string[user_count]{};
  std::cin.ignore(32767, '\n');
  for (std::int16_t i = 0; i < user_count; i++) {
    std::cout << "Pls enter " << i + 1 << " name:" << '\n';
    std::getline(std::cin, name_array[i]);
  }

  //сортировка массива в алфавитном порядке
  for (std::int16_t i = 0; i < user_count - 1; i++) {
    for (int j = 0; j < user_count - 1; j++) {
      if (name_array[j] > name_array[j + 1]) {
        std::swap(name_array[j], name_array[j + 1]);
      }
    }
  }

  //вывод всего моссива
  std::cout << "Here is your sorted array" << '\n';
  for (std::int16_t i = 0; i < user_count; i++) {
    std::cout << i << " member of name array is " << name_array[i] << '\n';
  }

  delete[] name_array;

  return EXIT_SUCCESS;
}
