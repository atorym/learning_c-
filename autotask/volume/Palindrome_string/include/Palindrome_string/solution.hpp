/*
 * Напишите программу, которая принимает от пользователя строку и проверяет, является ли она палиндромом (читается одинаково слева направо и справа налево).
 * Программа должна игнорировать пробелы и знаки препинания при проверке.
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <string_view>


namespace at::palindrome_string {


bool solution(std::string_view str);


} // namespace at::palindrome_string
