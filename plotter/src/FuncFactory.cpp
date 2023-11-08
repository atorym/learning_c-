//
// Created by dym on 04.11.23.
//

#include <math.h>
#include <plotter/FuncFactory.hpp>


namespace lc {

//расчет факториала
std::size_t factorial(std::size_t number) {
  std::size_t j = 1;
  for (std::size_t i = 1; i < number + 1; ++i) {
    j = j * i;
  }
  return j;
}
//расчет степени числа
double stepen_chisla(double chislo, std::size_t stepen) {
  double chislo_copy = chislo;
  for (std::size_t i = 1; i < stepen + 1; ++i) {
    chislo = chislo * chislo_copy;
  }
  return chislo;
}
//знак числа
double sign(double x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 0;
  }
}
//массив 2-ек
std::array<std::size_t, 30> array_of_two {3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61};
//расчет синуса
double my_sin(double x) {
  std::size_t i = 3;
  while (i != 30) {
    x += sign(x) * (stepen_chisla(x, array_of_two[i]) / factorial(array_of_two[i]));
    ++i;
  }
  return x;
}

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

    FuncPtr {new Func{
      .name = L"Гипербола",
      .previewArea{
        .xAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return 1 / x;
      },
    }},
    FuncPtr {new Func{
      .name = L"Синусоида",
      .previewArea{
        .xAxis{-5, 5},
      },
      .ptr = [](double x) -> double {
        return my_sin(x);
      },
    }},

  };
  return out;
}


}// namespace lc
