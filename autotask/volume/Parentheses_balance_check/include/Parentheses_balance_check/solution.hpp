/*
 *
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <string_view>


namespace at::parentheses_balance_check {


/**
 * @brief Проверяет сбалансированность скобок в строке.
 *
 * @param str Строка, содержащая скобки.
 * @return true, если скобки сбалансированы, иначе false.
 *
 * @details Функция принимает строку, содержащую скобки, и проверяет их сбалансированность.
 * В строке могут встречаться следующие типы скобок: `()`, `[]`, `{}`.
 * Скобки считаются сбалансированными, если для каждой открывающей скобки
 * есть соответствующая закрывающая скобка правильного типа и порядка.
 *
 * Пример использования:
 * @code
 * std::string str1 = "({})[]";
 * bool result1 = isBalanced(str1); // true
 *
 * std::string str2 = "{[()]}";
 * bool result2 = isBalanced(str2); // true
 *
 * std::string str3 = "{[}]";
 * bool result3 = isBalanced(str3); // false
 * @endcode
 *
 * Пример вывода:
 * Результат проверки будет true для сбалансированных строк и false для несбалансированных строк.
 */
bool solution(std::string_view str);


}// namespace at::parentheses_balance_check
