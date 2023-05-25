/*
 * Напишите программу, которая считывает числа с клавиатуры до тех пор, пока не будет введено отрицательное число.
 * После окончания ввода, программа должна вывести сумму всех положительных чисел, среднее арифметическое и максимальное из них.
 */

#include <at_2_4/solution.hpp>


namespace at::at_2_4 {


answer solution(std::istringstream&& iss) {
  answer_value current_value;
  answer out{};
  std::size_t counter{};
  while (true) {
    iss >> current_value;

    if (current_value<0){
      break;
    }

    out.sum += current_value;
    counter++;
    out.average=out.sum/counter;

    if(current_value>out.max){
      out.max=current_value;
    }
  }
  return out;
}


}// namespace at::at_2_4
