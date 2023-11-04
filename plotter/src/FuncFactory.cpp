//
// Created by dym on 04.11.23.
//

#include <plotter/FuncFactory.hpp>


namespace lc {


std::span<FuncFactory::Func const> FuncFactory::get() {
  static constexpr std::array out{
    Func{
      .name = "sin",
      .previewRange{-5, 5},
      .ptr = [](double x) -> double {
        return std::sin(x);
      },
    },
    Func{
      .name = "cos",
      .previewRange{-5, 5},
      .ptr = [](double x) -> double {
        return std::cos(x);
      },
    },
  };
  return out;
}


}// namespace lc
