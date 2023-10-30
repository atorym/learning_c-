cmake_minimum_required(VERSION 3.21)
project(test_and_do)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(external/fmt)
add_subdirectory(external/range-v3)


add_executable(test_and_do main.cpp)
target_link_libraries(test_and_do
  range-v3::range-v3
  fmt::fmt
  )
