//
// Created by dym on 04.11.23.
//

#include <plotter/FuncFactory.hpp>


namespace lc {


std::span<FuncFactory::FuncPtr const> FuncFactory::get() {
  static std::array out{
    FuncPtr{new Func{
      .name = L"sin",
      .previewArea{
        .xAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return std::sin(x);
      },
    }},

    FuncPtr{new Func{
      .name = L"cos",
      .previewArea{
        .xAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return std::cos(x);
      },
    }},

    FuncPtr{new Func{
      .name = L"парабола",
      .previewArea{
        .xAxis{-5, 5},
        .yAxis = Func::PreviewRange{0, 5 * 2},
      },
      .ptr = [](double x) -> double {
        return x * x;
      },
    }},

    FuncPtr{new Func{
      .name = L"arcsin",
      .previewArea{
        .xAxis{-2, 2},
      },
      .ptr = [](double x) -> double {
        return std::asin(x);
      },
    }},

  };
  return out;
}


}// namespace lc
