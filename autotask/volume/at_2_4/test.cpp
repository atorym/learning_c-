#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <service/helper.hpp>

#include <at_2_4/solution.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace at_2_4;
namespace rv = ranges::views;


TEST(autotask, at_2_4) {
  for (auto&& [str, expect] : {
         std::make_pair("3 5 -1"s, answer{8, 4, 5}),
         std::make_pair("3 5 -1 1 1 1 1"s, answer{8, 4, 5}),
         std::make_pair(ranges::accumulate(rv::iota(0, 101), std::string{}, [](auto&& str, auto i) {
           return std::forward<decltype(str)>(str) + std::to_string(i) + " ";
         }) + "-1", answer{5050, 50, 100}),
       }) {
    auto const answer = solution(std::istringstream{str});
    EXPECT_EQ(answer.sum, expect.sum);
    EXPECT_EQ(answer.average, expect.average);
    EXPECT_EQ(answer.max, expect.max);
  }
}


}// namespace at
