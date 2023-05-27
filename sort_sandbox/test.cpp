#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <random>

#include <service/helper.hpp>

#include <sandbox_sort/defines.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace sandbox_sort;


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
  std::array<device_type, numbers_needed> numbers{};
  std::random_device device{};
  std::generate(std::begin(numbers), std::end(numbers), std::ref(device));
  std::seed_seq seedseq{std::cbegin(numbers), std::cend(numbers)};
  return EngineT{seedseq};
}


template<typename T = std::mt19937>
T& random_engine() {
  static auto re = seed_non_deterministically_2nd();
  return re;
}


//template<typename T, typename RE = std::mt19937>
//T random(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
//}


}// namespace _
}// namespace


TEST(sandbox_sort, general) {
  _::random_engine();
}


}// namespace at