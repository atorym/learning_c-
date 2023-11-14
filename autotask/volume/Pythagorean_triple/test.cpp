#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <charconv>

#include <Pythagorean_triple/solution.hpp>


namespace at {


using namespace std::literals;
using namespace testing;
using namespace pythagorean_triple;


namespace {
namespace _ {


auto prepare_spit(auto ch, auto&& f) {
  namespace rv = ranges::views;
  return rv::split(ch)
         | rv::remove_if(ranges::empty)
         | rv::transform(std::forward<decltype(f)>(f));
}


rng_under_t to_int(std::string_view input) {
  rng_under_t out;
  auto const [ptr, ec] = std::from_chars(input.data(), input.data() + input.size(), out);
  if (ec != std::errc{} || &*input.cend() != ptr) {
    throw std::runtime_error{"NAN. str: "s + std::string{input}};
  }
  return out;
}


}// namespace _
}// namespace


TEST(autotask, pythagorean_triple) {
  struct set final {
    std::vector<std::array<rng_under_t, 3>> out;// mdspan
    rng_t rng;
  };
  std::ostringstream oss;
  for (auto&& [expect, rng] : {
         set{{
               {3, 4, 5},
               {6, 8, 10},
             },
           1, 10},
         /*
         set{{
               {3, 4, 5},
               {5, 12, 13},
               {6, 8, 10},
               {8, 15, 17},
               {9, 12, 15},
               {12, 16, 20},
               {15, 20, 25},
             },
           1, 30},
*/
         set{{
               {3, 4, 5},
               {5, 12, 13},
               {6, 8, 10},
               {7, 24, 25},
               {8, 15, 17},
               {9, 12, 15},
               {12, 16, 20},
               {15, 20, 25},
               {20, 21, 29},
               {28, 45, 53},
               {33, 44, 55},
               {36, 48, 60},
               {40, 42, 58},
             },
           1, 150},
       }) {
    solution(oss, rng);
    auto const answ_str = std::move(oss).str();
    ASSERT_FALSE(answ_str.empty()) << "Returned zero size string";
    // spirit x3?
    for (auto [line_answ, line_expect] :
      ranges::views::zip(
        answ_str | _::prepare_spit('\n', [](auto rng) {
          return rng | _::prepare_spit(' ', [](auto rng) {
            return _::to_int(std::string_view(&*rng.begin(), ranges::distance(rng)));
          });
        }),
        expect)) {
      ASSERT_THAT(line_expect, UnorderedElementsAreArray(line_answ | ranges::to<std::vector<rng_under_t>>)) << "Actual string:\n" << answ_str;
    }
  }
}


}// namespace at
