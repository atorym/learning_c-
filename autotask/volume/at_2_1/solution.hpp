/*
 * Напишите программу, которая принимает от пользователя три числа и определяет,
 * является ли треугольник с такими сторонами равносторонним, равнобедренным или разносторонним.
 */

#pragma once

#include <cstdint>
#include <cstdlib>


namespace at_2_1 {


enum class answer : std::uint8_t {
  equilateral, // равносторонний
  isosceles, // равнобедренный
  scalene, // разносторонний
};


answer solution(std::uint16_t a, std::uint16_t b, std::uint16_t c);


} // namespace at_2_1
