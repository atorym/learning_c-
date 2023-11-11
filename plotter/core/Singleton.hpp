//
// Created by dym on 01.10.22.
//

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>


namespace lc {


template<typename Derived>
class Singleton {
public:
  static Derived* init(auto&&... args) {
    assert(!p_ && "singleton has been initialized");
    // https://en.cppreference.com/w/cpp/memory/destroy_at
    // https://habr.com/ru/post/540954/
    alignas(Derived) static std::byte mem[sizeof(Derived)];
    return p_ = new (mem) Derived{std::forward<decltype(args)>(args)...};
  }


  [[nodiscard]] static Derived* instance() {
    if (!p_) {
      init();
    }
    return p_;
  }

public:
  ~Singleton() {
    if (p_) {
      p_->~Derived();
      p_ = nullptr;
    }
  }

protected:
  Singleton() noexcept = default;

private:
  static inline Derived* p_ = nullptr;
};


}// namespace lc
