/*
Задание №2
Определите перечисление (или класс enum) Animal, которое содержит следующих животных: pig, chicken,
goat, cat, dog и ostrich. Напишите функцию getAnimalName(), которая принимает параметр Animal и
использует switch для возврата типа животного в качестве строки. Напишите еще одну функцию — printNumberOfLegs(),
которая использует switch для вывода количества лап соответствующего типа животного. Убедитесь, что обе функции
имеют кейс default, который выводит сообщение об ошибке. Вызовите printNumberOfLegs() в main(), используя в
качестве параметров cat и chicken.
*/

#include <cstdint>
#include <iostream>
#include <string>

enum class animal_e {
  pig,
  chicken,
  goat,
  cat,
  dog,
  ostrich,
};

std::string get_animal_name(animal_e animal) {
  switch (animal) {
    case animal_e::pig:
      return "pig";
      break;
    case animal_e::chicken:
      return "chicken";
      break;
    case animal_e::goat:
      return "goat";
      break;
    case animal_e::cat:
      return "cat";
      break;
    case animal_e::dog:
      return "dog";
      break;
    case animal_e::ostrich:
      return "ostrich";
      break;
    default:
      return "animal not defined";
      break;
  }
}

std::uint16_t print_number_of_legs(animal_e animal) {
  switch (animal) {
    case animal_e::pig:
    case animal_e::goat:
    case animal_e::cat:
    case animal_e::dog:
      return 4;
      break;
    case animal_e::chicken:
    case animal_e::ostrich:
      return 2;
      break;
    default:
      std::cout << "ERROR";
  }
}

int main() {
std::cout << get_animal_name(animal_e::cat) << " has "
<< print_number_of_legs(animal_e::cat) << " legs\n"
    << get_animal_name(animal_e::chicken) << " has "
    <<print_number_of_legs(animal_e::chicken) << " legs\n";

  return 0;
}
