#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <service/helper.hpp>

#include <Palindrome_string/solution.hpp>


namespace at {


using namespace testing;
using namespace palindrome_string;


TEST(autotask, palindrome_string) {
  for (auto const [str, expected] : {
         std::make_pair("radar", true),
         std::make_pair("madam", true),
         std::make_pair("deified", true),
         std::make_pair("level", true),
         std::make_pair("hello", false),
         std::make_pair("openAI", false),
         std::make_pair("12321", true),
         std::make_pair("abcba", true),
         std::make_pair("python", false),
         std::make_pair("Able was I saw Elba", true),
       }) {
    bool const actual = solution(str);
    EXPECT_EQ(expected, actual)
      << std::boolalpha
      << "Wrong answer. Str: " << str
      << "\nexpected: " << expected
      << "\nactual: " << actual;
  }
}


}// namespace at
