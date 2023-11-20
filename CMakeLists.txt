cmake_minimum_required(VERSION 3.21)
project(learning_autotask CXX)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(external/gtest)
add_subdirectory(external/fmt)
add_subdirectory(external/range-v3)

function(target_link_extra_lib target)
  target_link_libraries(${target} PUBLIC
    range-v3::range-v3
    fmt::fmt
    )
endfunction()

function(target_pch target)
  target_precompile_headers(${target} PUBLIC
    "<range/v3/all.hpp>"
    "<fmt/printf.h>"
    "<fmt/format.h>"
    )
endfunction()


add_subdirectory(autotask)
add_subdirectory(sandbox)
