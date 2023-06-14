/*
 * Напишите программу, которая генерирует и выводит на экран все пифагоровы тройки чисел в заданном диапазоне.
 * Пифагорова тройка - это набор трех чисел (a, b, c), для которого выполняется условие a^2 + b^2 = c^2.
 * Порядок чисел в тройке не имеет значения. Порядок самих троек в возрастающий.
 * Выводить в формате:
 * d1 d2 d3
 * e1 e2 e3
 * Пример:
 * Ввод {1,10}
 * Ответ:
 * 4 3 5
 * 6 8 10
 */

#include <Pythagorean_triple/solution.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>


namespace at::pythagorean_triple {


void solution(std::ostringstream& oss, rng_t rng) {
  //записываем значения диапазона из структуры в переменные для лучшей читабельности
  std::int16_t hight_value = rng.hi;
  std::int16_t low_value = rng.low;
  //тело программы
  //грани треугольника
  std::int16_t a(low_value), b(low_value + 1), c(low_value + 2);
  for (; c < hight_value; ++c) {
    a = low_value;
    b = low_value + 1;
    for (std::int16_t c_value = c; a < c_value; ++a) {
      b = low_value + 1;
      for (; b < c_value; ++b) {
        if ((a * a + b * b) == (c * c)) {
          //выводим тройку
          oss << a << " "
              << b << " "
              << c << '\n';
        }
      }
    }
  }
}


}// namespace at::pythagorean_triple
