//
// Created by dym on 04.11.23.
//

#include <plotter/FuncFactory.hpp>


namespace lc {


std::span<FuncFactory::Func const> FuncFactory::get() {
  static constexpr std::array out{
    Func{
      .name = L"sin",
      .previewArea{
        .xAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return std::sin(x);
      },
    },
    Func{
      .name = L"cos",
      .previewArea{
        .xAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return std::cos(x);
      },
    },
    Func{
      .name = L"парабола",
      .previewArea{
        .xAxis{-5, 5},
        .yAxis = Func::PreviewRange{0, 5 * 2},
      },
      .ptr = [](double x) -> double {
        return x * x;
      },
    },
    Func{
      .name = L"arcsin",
      .previewArea{
        .xAxis{-2, 2},
      },
      .ptr = [](double x) -> double {
        return std::asin(x);
      },
    },
  };
  return out;
}


}// namespace lc
