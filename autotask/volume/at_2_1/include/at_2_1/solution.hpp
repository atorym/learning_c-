/*
 * Напишите программу, которая принимает от пользователя три числа и определяет, является ли треугольник с такими сторонами равносторонним, равнобедренным или разносторонним.
 */

#pragma once

#include <cstdint>
#include <cstdlib>


namespace at::at_2_1 {


enum class answer : std::uint8_t {
  equilateral, // равносторонний
  isosceles, // равнобедренный
  scalene, // разносторонний
};


answer solution(std::uint8_t a, std::uint8_t b, std::uint8_t c);


} // namespace at::at_2_1
