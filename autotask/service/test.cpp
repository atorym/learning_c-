#include <solution.hpp>

#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>


TEST(autotask, ${task_id}) {
  using namespace testing;
  using namespace ${task_namespace};

  EXPECT_EQ(Solution::<#initializer#>, <#initializer#>);
  EXPECT_THAT(Solution::<#initializer#>, ElementsAre(<#initializer#>));
}
