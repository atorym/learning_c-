//
// Created by dym on 04.11.23.
//

#pragma once

#include <memory>
#include <optional>
#include <span>
#include <string_view>


namespace lc {


class FuncFactory final {
public:
  struct Func final {
    std::wstring_view name;

    struct PreviewRange final {
      double min;
      double max;
    };
    struct PreviewArea final {
      PreviewRange                xAxis;
      std::optional<PreviewRange> yAxis;
    } previewArea;

    using Ptr = double (*)(double);
    Ptr ptr;
  };

  using FuncPtr = std::shared_ptr<Func const>;

public:
  FuncFactory() = delete;

  static std::span<FuncPtr const> get();
};


}// namespace lc
