#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <service/helper.hpp>

#include <palindromic_substrings/solution.hpp>


namespace at {


using namespace testing;
using namespace palindromic_substrings;


TEST(autotask, palindromic_substrings) {
  EXPECT_EQ(palindromic_count("abc"), 3);
  EXPECT_EQ(palindromic_count("aaa"), 6);
}


} // namespace at
