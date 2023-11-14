#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <range/v3/all.hpp>

#include <service_shared/helper.hpp>

#include <Parentheses_balance_check/solution.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace parentheses_balance_check;
namespace rv = ranges::views;


TEST(autotask, parentheses_balance_check) {
  for (auto const [str, expected] : {
         std::pair{"", true},
         std::pair{"([{", false},
         std::pair{"({})[]", true},
         std::pair{"{[()]}", true},
         std::pair{"[[]]", true},
         std::pair{"(){}[]", true},
         std::pair{"[({})]", true},
         std::pair{"{[}]", false},
         std::pair{"]()(", false},
         std::pair{"[({}])", false},
         std::pair{"[({}]", false},
         std::pair{"{[()}", false},
         std::pair{"]})", false},
         std::pair{"{[)]}", false},
         std::pair{"{[()]}}", false},
       }) {
    ASSERT_EQ(solution(str), expected) << "Wrong answer on str: " << str;
  }
}


}// namespace at
