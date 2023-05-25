#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <service/helper.hpp>

#include <at_2_1/solution.hpp>


namespace at {


using namespace testing;
using namespace at_2_1;


TEST(autotask, at_2_1) {
  for (auto const [expected, args] : {
         std::make_pair(answer::equilateral, std::make_tuple(arg_t{1}, arg_t{1}, arg_t{1})),
         std::make_pair(answer::equilateral, std::make_tuple(arg_t{0}, arg_t{0}, arg_t{0})),
         std::make_pair(answer::equilateral, std::make_tuple(std::numeric_limits<arg_t>::max(), std::numeric_limits<arg_t>::max(), std::numeric_limits<arg_t>::max())),
         std::make_pair(answer::isosceles, std::make_tuple(arg_t{1}, arg_t{1}, arg_t{10})),
         std::make_pair(answer::isosceles, std::make_tuple(arg_t{10}, arg_t{1}, arg_t{1})),
         std::make_pair(answer::isosceles, std::make_tuple(arg_t{1}, arg_t{10}, arg_t{1})),
         std::make_pair(answer::scalene, std::make_tuple(arg_t{1}, arg_t{10}, arg_t{100})),
       }) {
    std::apply([expected = expected, args_tuple = args](auto... args) {
      auto const answ = solution(args...);
      ASSERT_EQ(expected, answ)
        << "Wrong answer. Output: " << static_cast<int>(answ)
        << "\targs: " << PrintToString(args_tuple);
    }, args);
  }
}


}// namespace at
