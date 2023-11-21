#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <service/helper.hpp>

#include <is_palindrome/solution.hpp>


namespace at {


using namespace testing;
using namespace is_palindrome;


TEST(autotask, is_palindrome) {
  EXPECT_FALSE(is_palindrome_func("abc"));
  EXPECT_TRUE(is_palindrome_func("aaa"));
  EXPECT_TRUE(is_palindrome_func("aaaa"));
  EXPECT_TRUE(is_palindrome_func("a"));
  EXPECT_TRUE(is_palindrome_func("madam"));
  EXPECT_FALSE(is_palindrome_func("hello"));
  EXPECT_TRUE(is_palindrome_func("radar"));
  EXPECT_TRUE(is_palindrome_func(""));
}


} // namespace at
