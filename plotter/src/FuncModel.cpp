//
// Created by dym on 09.11.23.
//

#include <plotter/FuncModel.hpp>

#include <type_traits>

#include <plotter/colorAppointer.hpp>


namespace lc {


FuncModel::~FuncModel() = default;


FuncModel::FuncModel()
    : data_{
      FuncFactory::get() | ranges::views::transform([](auto const ptr) -> typename decltype(data_)::value_type {
        return {
          ptr,
          {
            .color = QString::fromStdString(colorAppointer()),
          },
        };
      })
      | ranges::to<decltype(data_)>} {
}


QVariant FuncModel::get(FuncFactory::FuncPtr const& fn, FuncModel::Role role) const {
  auto const& attr = data_.find(fn)->second;
  switch (role) {
    case Role::color:
      return attr.color;
    default:
      assert(false);
  }
}


void FuncModel::set(FuncFactory::FuncPtr fn, FuncModel::Role role, QVariant value) {
  auto const exchanger = [this, value, fn, role](auto mem) {
    auto&      cur = std::mem_fn(mem)(data_.find(fn)->second);
    auto const old = std::exchange(cur, value.value<std::remove_cvref_t<decltype(cur)>>());
    if (old != cur) {
      emit changed(fn, role, value, {});
    }
  };
  switch (role) {
    case Role::color:
      exchanger(&Attribute::color);
      break;
    default:
      assert(false);
  }
}


}// namespace lc
