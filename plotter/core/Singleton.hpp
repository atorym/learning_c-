//
// Created by dym on 01.10.22.
//

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>

#include <plotter/core/finally.hpp>


namespace lc {


enum class SingletonLivetimeMode : std::uint8_t {
  Global,
  ThreadLocal
};


namespace aux {


template<typename Derived_, SingletonLivetimeMode>
struct SingletonMem;


template<typename Derived_>
struct SingletonMem<Derived_, SingletonLivetimeMode::Global> {
  static inline Derived_* p_;

  // https://en.cppreference.com/w/cpp/memory/destroy_at
  // https://habr.com/ru/post/540954/
  static std::byte* memory() {
    alignas(Derived_) static std::byte mem_[sizeof(Derived_)];
    return mem_;
  }
};


template<typename Derived_>
struct SingletonMem<Derived_, SingletonLivetimeMode::ThreadLocal> {
  static thread_local inline Derived_* p_;


  static std::byte* memory() {
    alignas(Derived_) static thread_local std::byte mem_[sizeof(Derived_)];
    return mem_;
  }
};


}// namespace aux


template<typename Derived_, SingletonLivetimeMode LMode_ = SingletonLivetimeMode::ThreadLocal>
class Singleton : private aux::SingletonMem<Derived_, LMode_> {
private:
  using Derived = Derived_;
  using Mem     = aux::SingletonMem<Derived_, LMode_>;

public:
  static Derived* init(auto&&... args) {
    assert(!Mem::p_ && "singleton has been initialized");
    Mem::p_ = new (Mem::memory()) Derived{std::forward<decltype(args)>(args)...};
    return instance();
  }


  [[nodiscard]] static Derived* instance() {
    assert(Mem::p_ && "singleton not initialized");
    return Mem::p_;
  }


  static void destroy() {
    if (Mem::p_) {
      Mem::p_->~Derived();
      Mem::p_ = nullptr;
    }
  }

protected:
  Singleton() noexcept = default;

private:
  [[maybe_unused]] static inline auto const destroy_auto_ = finally([] { destroy(); });
};


}// namespace lc