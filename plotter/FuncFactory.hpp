//
// Created by dym on 04.11.23.
//

#pragma once

#include <span>
#include <string_view>


namespace lc {


class FuncFactory final {
public:
  struct Func final {
    std::string_view name;

    struct PreviewRange final {
      double min;
      double max;
    };
    struct PreviewArea final {
      PreviewRange xAxis;
      PreviewRange yAxis;
    } previewArea;

    using Ptr = double (*)(double);
    Ptr ptr;
  };

public:
  FuncFactory() = delete;

  static std::span<Func const> get();
};


}// namespace lc
