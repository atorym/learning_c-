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

#pragma once

#include <cstdint>
#include <cstdlib>
#include <sstream>


namespace at::pythagorean_triple {


using rng_under_t = std::uint16_t;


struct rng_t final {
  rng_under_t low;
  rng_under_t hi;
};


void solution(std::ostringstream& oss, rng_t rng);


}// namespace at::pythagorean_triple
