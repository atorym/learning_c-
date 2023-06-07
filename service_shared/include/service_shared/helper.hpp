//
// Created by dym on 07.06.23.
//

#pragma once

#include <ostream>
#include <span>


namespace at {


/* blyat ne rabotaet1!!
template<typename It>
void printer(std::ostream& os, It b, It e) {
  os << '{';
  if (std::distance(b, e) == 0) {
    os << "empty";
  } else {
    for (auto&& i : ranges::subrange{b, e} | ranges::views::join(',')) {
      os << i;
    }
  }
  os << '}' << std::endl;
}


template<typename T, auto Extent = std::dynamic_extent>
std::ostream& operator<<(std::ostream& os, std::span<T, Extent> span) {
  printer(os, span.begin(), span.end());
  return os;
}
*/


template<typename T, auto Extent = std::dynamic_extent>
std::ostream& operator<<(std::ostream& os, std::span<T, Extent> span) {
  os << '[';
  if (span.empty()) {
    os << "empty";
  } else {
    os << span[0];
    for (std::size_t i = 1; i < span.size(); ++i) {
      os << ',' << span[i];
    }
  }
  os << ']' << std::endl;
  return os;
}



}// namespace at