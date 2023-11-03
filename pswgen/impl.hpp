//
// Created by adm on 22.10.2023.
//

#pragma once

#include <cstdint>
#include <iosfwd>
#include <vector>


namespace pg {


struct ImplContext final {
  /// @brief набор символов для ручного режима
  std::vector<char> manual_set;

  ///@ длинна пароля
  struct {
    std::size_t min;
    std::size_t max;
  } range;

  ///@brief потребное количество
  std::size_t count;

  /// @brief стрим для вывод на дисплей
  std::ostream& os_display;

  /// @brief стрим для вывода в файл
  std::ostream* os_file = nullptr;

  /// @brief bitmask требуемого режима
  enum Mode : std::uint8_t {
    number    = 1 << 0,
    letter    = 1 << 1,
    upper     = 1 << 2,
    character = 1 << 3,
    manual    = 1 << 4,
  } mode;
};


void impl(ImplContext const& ctx);


}// namespace pg