/*
Тест
 Напишите прототипы для каждой из следующих функций. Используйте наиболее подходящие параметры
 и типы возврата (по значению, по адресу или по ссылке). Используйте const, когда это необходимо.
Задание №1
 Функция sumTo(), которая принимает целочисленный параметр, а возвращает сумму всех чисел между 1
 и числом, которое ввел пользователь.
Задание №2
 Функция printAnimalName(), которая принимает структуру Animal в качестве параметра.
Задание №3
 Функция minmax(), которая принимает два целых числа в качестве входных данных, а возвращает
 наименьшее и наибольшее числа в качестве отдельных параметров.
Задание №4
 Функция getIndexOfLargestValue(), которая принимает целочисленный массив (как указатель) и его
 размер, а возвращает индекс наибольшего элемента массива.
Задание №5
 Функция getElement(), которая принимает целочисленный массив (как указатель) и индекс, а возвращает
 элемент массива по этому индексу (не копию элемента). Предполагается, что индекс корректен,
 а возвращаемое значение — константное.
*/

#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>


//задание 1
std::size_t sum_to(const std::size_t n) {
  std::size_t summ = 0;
  for (std::size_t i = 1; i <= n; ++i) {
    summ += i;
  }
  return summ;
}

//задание 2
struct animal {
  std::string name;
  std::size_t legs;
  std::size_t ass_hole;
};

void print_animal_name(animal& bober) {
}

//задание 3
void minmax(std::size_t lhs, std::size_t rhs, std::size_t& out_min, std::size_t& out_max) {
  if (lhs < rhs) {
    out_max = rhs;
    out_min = lhs;
  } else {
    out_max = lhs;
    out_min = rhs;
  }
}

//задание 4
std::size_t get_index_of_largest_value(std::size_t* array, std::size_t size) {
  std::size_t max = 0;
  std::size_t max_index = 0;
  for (std::size_t i = 0; i < size; ++i) {
    if (max < array[i]) {
      max = array[i];
      max_index = i;
    }
  }
  return max_index;
}

//задание 5
std::size_t const& get_element(std::size_t* array, std::size_t index) {
  return array[index];
}


int main() {


  return EXIT_SUCCESS;
}
