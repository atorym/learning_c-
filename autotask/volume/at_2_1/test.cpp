#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <service/helper.hpp>

#include <at_2_1/solution.hpp>


using namespace testing;
using namespace at::at_2_1;


TEST(autotask, at_2_1) {
  for (auto const [a, args] : {
         std::make_pair(answer::equilateral, std::make_tuple(1, 1, 1))}) {
    std::apply([a](auto... args) {
      ASSERT_EQ(a, solution(args...));
    }, args);
  }
}
