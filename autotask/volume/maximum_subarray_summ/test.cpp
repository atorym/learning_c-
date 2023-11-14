#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <array>

#include <range/v3/all.hpp>

#include <service_shared/helper.hpp>

#include <maximum_subarray_summ/solution.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace maximum_subarray_summ;
namespace rv = ranges::views;


#define MAKE_SET(answ, ...)                          \
  std::pair {                                        \
    static_cast<array_t (*)()>([]() -> array_t {     \
      static constexpr element_t arr[]{__VA_ARGS__}; \
      return arr;                                    \
    }),                                              \
      answ                                           \
  }


TEST(autotask, maximum_subarray_summ) {
  for (auto const [arr, expect] : {
         MAKE_SET(6, -2, 1, -3, 4, -1, 2, 1, -5, 4),
         MAKE_SET(9, 1, -2, 3, -4, 5, -6, 7, -8, 9),
         MAKE_SET(-1, -1, -2, -3, -4, -5),
         MAKE_SET(21, 5, -2, 6, -3, 7, -4, 8, -5, 9),
         MAKE_SET(-10, -10, -10, -10, -10),
       }) {
    auto const in = arr();
    ASSERT_EQ(solution(in), expect);
  }
}


}// namespace at
