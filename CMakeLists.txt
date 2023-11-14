cmake_minimum_required(VERSION 3.16.3)
project(learning_cpp CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/gtest)
add_subdirectory(external/fmt)
add_subdirectory(external/range)

function(target_link_extra_lib name)
  target_link_libraries(${name} PUBLIC
    range-v3
    fmt
    )
endfunction()

function(target_pch name)
  target_precompile_headers(${name} PUBLIC
    "<range/v3/all.hpp>"
    "<fmt/printf.h>"
    "<fmt/format.h>"
    "<fmt/ranges.h>"
    )
endfunction()

add_subdirectory(service_shared)
add_subdirectory(autotask)
add_subdirectory(sandbox)
add_subdirectory(sort_sandbox)
