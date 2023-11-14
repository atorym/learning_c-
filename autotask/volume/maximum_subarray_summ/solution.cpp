#include <maximum_subarray_summ/solution.hpp>


namespace at::maximum_subarray_summ {


result_t solution(array_t arr) {
  result_t max_so_far = std::numeric_limits<result_t>::max();
  result_t max_ending_here = 0;

  for (auto i : arr) {
    max_ending_here = max_ending_here + i;
    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
    }

    if (max_ending_here < 0) {
      max_ending_here = 0;
    }
  }
  return max_so_far;
}


}// namespace at::maximum_subarray_summ
