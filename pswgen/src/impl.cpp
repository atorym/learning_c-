//
// Created by dym on 23.10.23.
//

#include <pswgen/impl.hpp>

#include <ostream>
#include <random>


namespace pg {
namespace {
namespace _ {


}
}// namespace


//НАЧАЛО КОДА АРТёМА
std::size_t mersenne_range(std::size_t, std::size_t);
void array_sum(auto& array1, auto& array2) {
  for (std::size_t i = 0; i < array2.size(); ++i) {
    array1.push_back(array2[i]);
  }
}


void impl(ImplContext const& ctx) {

  //создаем буферный массив, который будет заполнятся в зависимости от выбранных диапазонов рандомизации
  std::vector<char> buffer;
  //очищаем буфер от мусора

  std::vector<char> numbers_bank{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  std::vector<char> letters_bank{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
  std::vector<char> upper_bank{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
  std::vector<char> character_bank{',', '.', '/', '[', ']', '{', '}', ':', '<', '>', '?'};

  if (ctx.mode & ctx.number) {
    array_sum(buffer, numbers_bank);
  }
  if (ctx.mode & ctx.letter) {
    array_sum(buffer, letters_bank);
  }
  if (ctx.mode & ctx.upper) {
    array_sum(buffer, upper_bank);
  }
  if (ctx.mode & ctx.character) {
    array_sum(buffer, character_bank);
  }
  if (ctx.mode & ctx.manual) {
    array_sum(buffer, ctx.manual_set);
  }

  //генерируем и выводим пароли х раз, х-го размера
  for (std::size_t i = 0; i < ctx.count; ++i) {
    for (std::size_t j = 0; j < mersenne_range(ctx.range.min, ctx.range.max); ++j) {
      std::size_t symbol_number;
      //генерируем рандомный итератор массива
      symbol_number = mersenne_range(0, buffer.size());
      //выводим символ привязанный за соответствующим итератором
      ctx.os_display << buffer[symbol_number];
    }
    ctx.os_display << '\n';
  }


  //очищаем буфер от мусора
  buffer.clear();
}

std::size_t mersenne_range(std::size_t min, std::size_t max) {
  //Настройка генератора случайных чисел Вихря Мерсенна.
  std::random_device rd;
  std::mt19937 mersenne(rd());
  //Генерация случайного числа в заданном диапазоне
  std::uniform_int_distribution distrib(min, max);
  return distrib(mersenne);
}


//КОНЕЦ КОДА АРТёМА


}// namespace pg