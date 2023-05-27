#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <range/v3/all.hpp>

#include <random>

#include <service/helper.hpp>

#include <sandbox_sort/defines.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace sandbox_sort;
namespace rv = ranges::views;


namespace {
namespace _ {


// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0205r1.html
template<typename EngineT = std::mt19937, std::size_t StateSize = EngineT::state_size>
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


template<typename T = std::mt19937>
T& random_engine() {
  static auto re = seed_non_deterministically_2nd();
  return re;
}


template<typename T, typename RE = std::mt19937>
T random(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
  return std::conditional_t<
    std::is_floating_point_v<T>,
    std::uniform_real_distribution<T>,
    std::uniform_int_distribution<T>>{min, max}(random_engine<RE>());
}


}// namespace _
}// namespace


TEST(sandbox_sort, general) {
  for (auto const i : rv::generate_n([] {
         return _::random(0, 10);
       },
         100)) {
    std::cout << i << ' ';
  }
}


}// namespace at