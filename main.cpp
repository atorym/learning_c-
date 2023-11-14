/*
Задание №4
 Напишите функцию для вывода строки C-style символ за символом. Используйте указатель
 для перехода и вывода каждого символа поочерёдно. Остановите вывод при столкновении
 с нуль-терминатором. В функции main() протестируйте строку Hello, world!.
 */

#include <cstdlib>
#include <iostream>
#include <vector>


void print_c_stile_string(const char[], auto, auto);


int main() {
  constexpr char c_stile_string[] = "Hello world!";
  const auto begin{std::begin(c_stile_string)};
  const auto end{std::end(c_stile_string)};
  print_c_stile_string(c_stile_string, begin, end);

  return EXIT_SUCCESS;
}


void print_c_stile_string(const char c_stile_string[], auto begin, auto end) {
  for (auto i{begin}; i != end; ++i) {
    std::cout << *i;
  }
}