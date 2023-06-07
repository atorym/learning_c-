#include <sandbox_sort/defines.hpp>
#include <utility>

namespace at::sandbox_sort {


array_t sort(array_t in) {
  const std::size_t size_of_array = std::size(in);

  for (std::size_t i = 0; i < size_of_array - 1; ++i) {
    for (std::size_t j = i+1; j < size_of_array; ++j){
      if (in[i] > in[i + 1]) {
        std::swap(in[i], in[j]);
      }
    }
  }
  return in;
}


}// namespace at::sandbox_sort
