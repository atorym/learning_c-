/*
 * Напишите программу, которая принимает от пользователя три числа и определяет, является ли треугольник с такими сторонами равносторонним, равнобедренным или разносторонним.
 */

#pragma once

#include <cstdint>
#include <cstdlib>


namespace at::at_2_1 {


using arg_t = std::uint16_t;


enum class answer : std::uint8_t {
  equilateral,// равносторонний
  isosceles,  // равнобедренный
  scalene,    // разносторонний
};


answer solution(arg_t a, arg_t b, arg_t c);


}// namespace at::at_2_1
