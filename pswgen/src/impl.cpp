//
// Created by dym on 23.10.23.
//

#include <pswgen/impl.hpp>


namespace pg {
namespace {
namespace _ {


auto random_engine = [] {
  std::random_device rd{};
  return std::mt19937{rd()};
}();


}
}// namespace


//НАЧАЛО КОДА АРТёМА
std::size_t mersenne_range(std::size_t, std::size_t);
void array_summ(std::vector<char>, std::vector<char>);


void impl(ImplContext const& ctx) {

  //создаем буфферный массив, который будет наполнятся в зависимости от выбранных диапазонов рандомизации
  std::vector<char> buffer;
  //очищаем буфер от мусора
  buffer.clear();

  std::vector<char> numbers_bank{'1','2','3','4','5','6','7','8','9','0'};
  std::vector<char> letters_bank{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
  std::vector<char> upper_bank{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
  std::vector<char> character_bank{',', '.', '/', '[', ']', '{', '}', ':', '<', '>', '?'};

  std::size_t flag;
  if (ctx.mode & ctx.number) {
    array_summ(buffer, numbers_bank);
  }
  if (ctx.mode & ctx.letter) {
    array_summ(buffer, letters_bank);
  }
  if (ctx.mode & ctx.upper) {
    array_summ(buffer, upper_bank);
  }
  if (ctx.mode & ctx.character) {
    array_summ(buffer, character_bank);
  }
  if (ctx.mode & ctx.manual) {
    array_summ(buffer, ctx.manual_set);
  }

  //генерируем и выводим пароли х раз, х-го размера
  for (std::size_t i = 0; i < ctx.count; ++i) {
    for (std::size_t i = 0; i < mersenne_range(ctx.range.min, ctx.range.max); i++) {
      std::size_t symbol_number;
      //генерируем рандомный итератор массива
      symbol_number = mersenne_range(buffer.front(), buffer.back());
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
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(mersenne);
}

//функция push_back одного массива к другому
void array_summ(std::vector<char>& array1, std::vector<char>& array2) {
  for (std::size_t i = 0; i < array2.size(); ++i) {
    array1.push_back(array2[i]);
  }
}

//КОНЕЦ КОДА АРТёМА


}// namespace pg