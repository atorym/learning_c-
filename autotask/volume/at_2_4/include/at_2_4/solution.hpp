/*
 * Напишите программу, которая считывает числа с клавиатуры до тех пор, пока не будет введено отрицательное число.
 * После окончания ввода, программа должна вывести сумму всех положительных чисел, среднее арифметическое и максимальное из них.
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <sstream>


namespace at::at_2_4 {


using answer_value = double;


struct answer final {
  answer_value sum;
  answer_value average;
  answer_value max;
};


answer solution(std::istringstream&& iss);


}// namespace at::at_2_4
