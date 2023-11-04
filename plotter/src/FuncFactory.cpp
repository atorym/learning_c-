//
// Created by dym on 04.11.23.
//

#include <plotter/FuncFactory.hpp>


namespace lc {


std::span<FuncFactory::Func const> FuncFactory::get() {
  static constexpr std::array out{
    Func{
      .name = "sin",
      .previewArea{
        .xAxis{-5, 5},
        .yAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return std::sin(x);
      },
    },
    Func{
      .name = "cos",
      .previewArea{
        .xAxis{-5, 5},
        .yAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return std::cos(x);
      },
    },
    Func{
      .name = "Parabolic",
      .previewArea{
        .xAxis{-5, 5},
        .yAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        int a = x;
        return a*a;
      },
    },
  };
  return out;
}


}// namespace lc
