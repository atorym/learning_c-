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
#include <stdexcept>
#include <string>


using literal_string = char const*;


enum class animal_t : std::uint8_t {
  pig,
  chicken,
  goat,
  cat,
  dog,
  ostrich,
};


literal_string get_animal_name(animal_t animal) {
  switch (animal) {
    case animal_t::pig:
      return "pig";
    case animal_t::chicken:
      return "chicken";
    case animal_t::goat:
      return "goat";
    case animal_t::cat:
      return "cat";
    case animal_t::dog:
      return "dog";
    case animal_t::ostrich:
      return "ostrich";
    default:
      throw std::logic_error{"animal not defined"};
  }
}


std::uint16_t print_number_of_legs(animal_t animal) {
  switch (animal) {
    case animal_t::pig:
    case animal_t::goat:
    case animal_t::cat:
    case animal_t::dog:
      return 4;
    case animal_t::chicken:
    case animal_t::ostrich:
      return 2;
    default:
      throw std::logic_error{"ERROR"};
  }
}


int main() {
  std::cout << get_animal_name(animal_t::cat) << " has "
            << print_number_of_legs(animal_t::cat) << " legs\n"
            << get_animal_name(animal_t::chicken) << " has "
            << print_number_of_legs(animal_t::chicken) << " legs\n";
  return EXIT_SUCCESS;
}
