/*
Методы программирования в примерах и задачах 2023 Валединский, Корнев
  Задача 1-10-12. Определите, сколько палиндромов содер-
  жится в заданной символьной строке char s[n].
  Указание. Если реализовать функцию подсчета всех
  палиндромов с центром в s[i] и ее модификацию для работы
  с палиндромами четной длины, то окончательная сложность
  составит O(n2 ) действий. Для решения задачи с линейной
  асимптотикой можно применить алгоритм Манакера.

https://leetcode.com/problems/palindromic-substrings
*/

#pragma once

#include <cstdint>
#include <cstdlib>
#include <string_view>


namespace at::palindromic_substrings {


std::size_t palindromic_count(std::string_view in);


} // namespace at::palindromic_substrings
