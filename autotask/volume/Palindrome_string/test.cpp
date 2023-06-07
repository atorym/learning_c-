#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <Palindrome_string/solution.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace palindrome_string;


TEST(autotask, palindrome_string) {
  for (auto const [str, expected] : {
         std::make_pair("radar"sv, true),
         std::make_pair("madam"sv, true),
         std::make_pair("deified"sv, true),
         std::make_pair("level"sv, true),
         std::make_pair("hello"sv, false),
         std::make_pair("openAI"sv, false),
         std::make_pair("12321"sv, true),
         std::make_pair("abcba"sv, true),
         std::make_pair("python"sv, false),
         std::make_pair("Able was I saw Elba"sv, true),
       }) {
    ASSERT_EQ(expected, solution(str)) << "Wrong answer. Str: " << str;
  }
}


}// namespace at
