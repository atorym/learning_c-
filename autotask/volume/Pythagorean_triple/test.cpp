#include <gtest/gtest.h>
// GMock matches
// http://google.github.io/googletest/reference/matchers.html
// https://stackoverflow.com/questions/1460703/comparison-of-arrays-in-google-test
#include <gmock/gmock-matchers.h>
//#include <gmock/gmock-more-matchers.h>

#include <charconv>
#include <optional>

#include <service/helper.hpp>

#include <Pythagorean_triple/solution.hpp>


namespace at {


using namespace testing;
using namespace pythagorean_triple;


namespace {
namespace _ {


// https://stackoverflow.com/a/65675200
std::optional<rng_under_t> to_int(std::string_view input) {
  rng_under_t out;
  std::from_chars_result const result = std::from_chars(input.data(), input.data() + input.size(), out);
  if (result.ec != std::errc{}) {
    return std::nullopt;
  }
  return out;
}


}// namespace _
}// namespace


TEST(autotask, pythagorean_triple) {
  struct set final {
    std::vector<std::vector<rng_under_t>> out;// mdspan
    rng_t rng;
  };
  std::ostringstream oss;
  for (auto&& [out, rng] : {
         set{{
               {3, 4, 5},
               {6, 8, 10},
             },
           1, 10},
         //         set{{
         //               {3, 4, 5},
         //               {5, 12, 13},
         //               {6, 8, 10},
         //               {8, 15, 17},
         //               {9, 12, 15},
         //               {12, 16, 20},
         //               {15, 20, 25},
         //             },
         //           1, 30},
         //         set{{
         //               {3, 4, 5},
         //               {5, 12, 13},
         //               {6, 8, 10},
         //               {7, 24, 25},
         //               {8, 15, 17},
         //               {9, 12, 15},
         //               {12, 16, 20},
         //               {15, 20, 25},
         //               {20, 21, 29},
         //               {28, 45, 53},
         //               {33, 44, 55},
         //               {36, 48, 60},
         //               {40, 42, 58},
         //             },
         //           1, 150
         //         },
       }) {
    solution(oss, rng);
    auto const answ_str = std::move(oss).str();
    namespace rv = ranges::views; // spirit x3?
    auto const tmp = answ_str
      | rv::split('\n')
      | rv::transform([](auto&& rng) {
          return std::forward<decltype(rng)>(rng)
                 | rv::split(' ')
                 | rv::transform([](auto&& rng) {
                     return _::to_int(std::string_view(&*rng.begin(), ranges::distance(rng))).value();
                   })
                 | ranges::to<std::vector<rng_under_t>>;
        })
      | ranges::to<decltype(set::out)>;
    for (auto i : tmp) {
      for (auto const j : i) {
        std::cout << j << ' ';
      }
      std::cout << '\n';
    }
  }
}


}// namespace at
