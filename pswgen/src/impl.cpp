//
// Created by dym on 23.10.23.
//

#include <pswgen/impl.hpp>

#include <ostream>
#include <random>


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


void array_sum(auto& array1, auto const& array2) {
  for (std::size_t i = 0; i < array2.size(); ++i) {
    array1.push_back(array2[i]);// 🤙
  }
}


void impl(ImplContext const& ctx) {
  //создаем буферный массив, который будет заполнятся в зависимости от выбранных диапазонов рандомизации
  std::vector<char> buffer;

  if (ctx.mode & ImplContext::Mode::number) {
    std::array constexpr bank{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    array_sum(buffer, bank);
  }
  if (ctx.mode & ImplContext::Mode::letter) {
    std::array constexpr bank{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    array_sum(buffer, bank);
  }
  if (ctx.mode & ImplContext::Mode::upper) {
    std::array constexpr bank{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
    array_sum(buffer, bank);
  }
  if (ctx.mode & ImplContext::Mode::character) {
    std::array constexpr bank{'%', '*', ')', '?', '@', '#', '$', '~'};
    array_sum(buffer, bank);
  }
  if (ctx.mode & ImplContext::Mode::manual) {
    array_sum(buffer, ctx.manual_set);
  }

  //генерируем и выводим пароли х раз, х-го размера
  if (!buffer.empty()) {
    for (std::size_t i = 0; i < ctx.count; ++i) {
      for (std::size_t j = 0; j < mersenne_range(ctx.range.min, ctx.range.max); ++j) {

        ctx.os_display << buffer.at(mersenne_range(0, buffer.size()-1));
      }
      ctx.os_display << '\n';
    }
  }
}


std::size_t mersenne_range(std::size_t min, std::size_t max) {
  //Генерация случайного числа в заданном диапазоне
  return std::uniform_int_distribution{min, max}(_::random_engine);
}


//КОНЕЦ КОДА АРТёМА


}// namespace pg