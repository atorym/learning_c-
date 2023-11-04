//
// Created by dym on 06.10.23.
//

#pragma once

#include <utility>


namespace lc {


template<typename F>
constexpr auto finally(F&& f) {
  class Action {
  public:
    Action(Action const&) = delete;


    constexpr Action(F&& f)
        : f_{std::move(f)} {
    }


    constexpr Action(Action&& other)
        : f_{std::move(other.f_)} {
      other.active_ = false;
    }


    constexpr ~Action() {
      if (active_) {
        f_();
      }
    }


  private:
    F    f_;
    bool active_ = true;
  };

  return Action{std::forward<F>(f)};
}


}// namespace lc