#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <range/v3/all.hpp>

#include <random>

#include <sandbox_sort/defines.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace sandbox_sort;
namespace rv = ranges::views;


namespace {
namespace _ {


using RE = std::mt19937;


// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0205r1.html
template<typename EngineT = RE, std::size_t StateSize = EngineT::state_size>
EngineT seed_non_deterministically_2nd() {
  using engine_type = typename EngineT::result_type;
  using device_type = std::random_device::result_type;
  using seedseq_type = std::seed_seq::result_type;
  constexpr auto bytes_needed = StateSize * sizeof(engine_type);
  constexpr auto numbers_needed = (sizeof(device_type) < sizeof(seedseq_type))
                                    ? (bytes_needed / sizeof(device_type))
                                    : (bytes_needed / sizeof(seedseq_type));
  std::random_device rd{};
  auto rng_num = rv::generate_n(std::ref(rd), numbers_needed) | rv::common;
  std::seed_seq seedseq{rng_num.begin(), rng_num.end()};
  return EngineT{seedseq};
}


template<typename T = RE>
T& random_engine() {
  static auto re = seed_non_deterministically_2nd();
  return re;
}


template<typename T, typename RE = RE>
T random(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
  return std::conditional_t<
    std::is_floating_point_v<T>,
    std::uniform_real_distribution<T>,
    std::uniform_int_distribution<T>>{min, max}(random_engine<RE>());
}


array_t make_array(array_t&& arr, std::size_t to) {
  return std::move(arr) | ranges::actions::push_back(rv::iota(0u, to));
}


array_t make_array_downward(array_t&& arr, std::size_t from) {
  if (from > 1) {
    return make_array_downward(make_array(std::move(arr), from), from - 1);
  }
  return std::move(arr);
}


}// namespace _
}// namespace


TEST(sandbox_sort, general) {
  constexpr auto max = 2000;
  constexpr auto factor_lo = 0.01;
  constexpr auto n_lo = 5;
  for (auto const [get, msg] : {
       std::pair{static_cast<array_t (*)()>([] {
         return rv::iota(0, 10) | ranges::to<array_t>;
       }), "0..lo"},
       std::pair{static_cast<array_t (*)()>([] {
         return rv::iota(0, 10) | rv::reverse | ranges::to<array_t>;
       }), "0..lo reverse"},
       std::pair{static_cast<array_t (*)()>([] {
         return array_t{};
       }), "empty"},
       std::pair{static_cast<array_t (*)()>([] {
         auto out = _::make_array({}, max * factor_lo);
         ranges::shuffle(out, _::random_engine());
         return out;
       }), "0..lo shuffled"},
       std::pair{static_cast<array_t (*)()>([] {
         auto out = _::make_array({}, max);
         ranges::shuffle(out, _::random_engine());
         return out;
       }), "0..max shuffled"},
       std::pair{static_cast<array_t (*)()>([] {
         return rv::repeat(std::numeric_limits<element_t>::min()) | rv::take(n_lo) | ranges::to<array_t>;
       }), "n_lo min"},
       std::pair{static_cast<array_t (*)()>([] {
         return rv::repeat(std::numeric_limits<element_t>::max()) | rv::take(n_lo) | ranges::to<array_t>;
       }), "n_lo max"},
       std::pair{static_cast<array_t (*)()>([] {
         return rv::generate_n([] {
           return _::random<element_t>();
         }, max * factor_lo) | ranges::to<array_t>;
       }), "rand lo"},
       std::pair{static_cast<array_t (*)()>([] {
         return rv::generate_n([] {
           return _::random<element_t>();
         }, max) | ranges::to<array_t>;
       }), "rand max"},
       std::pair{static_cast<array_t (*)()>([] {
         auto out = _::make_array_downward({}, max * factor_lo);
         ranges::shuffle(out, _::random_engine());
         return out;
       }), "0..lo pyramid"},
       std::pair{static_cast<array_t (*)()>([] {
         auto out = _::make_array_downward({}, max);
         ranges::shuffle(out, _::random_engine());
         return out;
       }), "0..max pyramid"},
     }) {
    array_t const source = get();
    ASSERT_THAT(source, WhenSorted(sort(source))) << "Wrong answer. " << msg;
  }
}


}// namespace at