//
// Created by dym on 25.05.23.
//

#pragma once

#include <ostream>
#include <tuple>


namespace at {


template<typename... T>
std::ostream& operator<<(std::ostream& os, std::tuple<T...> const& ts) {
  std::apply([&os](auto&& first, auto&&... args) {
    os << first;
    ((os << ' ' << args), ...);
  },
    ts);
  return os;
}


}// namespace at